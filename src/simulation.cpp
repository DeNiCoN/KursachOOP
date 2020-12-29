#include "simulation.hpp"
#include "processes.hpp"

namespace transport
{
    using namespace processes;

    Simulation::Simulation(Graphics& graphics, ProcessManager& p_manager)
        : graphics_(graphics), p_manager_(p_manager), graph_(100000)
    {

    }

    void Simulation::AddVehicle(VehiclePtr vehicle_ptr, std::string start_position)
    {
        auto& info = vehicles_[vehicle_ptr->GetName()];
        info.ptr = std::move(vehicle_ptr);
        info.current_vertex = vertices_.at(start_position);

        Route(info);
    }

    void Simulation::AddVertex(VertexPtr vertex_ptr)
    {
        graphics_.AddVertex(vertex_ptr->GetName(), *vertex_ptr.get());
        auto id = graph_.AddVertex(vertex_ptr->GetTypes());
        auto& info = vertices_id[id];
        info.ptr = std::move(vertex_ptr);
        info.graph_id = id;

        vertices_[info.ptr->GetName()] = id;
    }

    void Simulation::AddRoad(const std::string& from, const std::string& to, double length)
    {
        graphics_.AddRoad(from, to, length);

        graph_.AddEdge(vertices_.at(from),
                       vertices_.at(to), length);
    }

    void Simulation::Route(VehicleInfo& info)
    {
        auto next_type = info.ptr->GetNextVertexType();
        int next_id = -1;

        if (next_type)
        {
            next_id = graph_.GetRandVertex(*next_type);
            if (next_id == -1)
            {
                next_id = graph_.GetRandVertex();
            }
        }
        else
        {
            next_id = graph_.GetRandVertex();
        }

//        std::cout << next_id << "\tnext_id" << std::endl;
        int current_id = info.current_vertex;

        auto route_queue = router_.FindRoute(graph_, current_id, next_id);

        ProcessPtr first;
        if (route_queue.size() < 2)
        {
            //No route found or next_id is the same as current
            //Visit current and look for next

            auto& end_info = vertices_id.at(next_id);
            first = VisitAndLookNext(info, end_info);
        }
        else
        {
            auto& first_info = vertices_id.at(route_queue[0]);
            auto& second_info = vertices_id.at(route_queue[1]);
            first = Ride(info, first_info, second_info);
            Process* last = first.get();

            for (size_t i = 1; i < route_queue.size() - 1; ++i)
            {
                auto& current_info = vertices_id.at(route_queue[i]);
                auto& next_info = vertices_id.at(route_queue[i + 1]);
                auto next = PassAndRide(info, current_info, next_info);

                last->SetNext(std::move(next));
                last = last->GetNext();
            }

            auto& end_info = vertices_id.at(route_queue.back());

            last->SetNext(VisitAndLookNext(info, end_info));
            last = last->GetNext();
        }

        p_manager_.Add(std::move(first));
    }

    ProcessPtr Simulation::VisitAndLookNext(VehicleInfo& veh, VertexInfo& end_info)
    {
        int id = end_info.graph_id;
        return ToPtr(
            MakeConsecutive(
                Callback([name = end_info.ptr->GetName()]() { std::cout << "vehicle visit vertex " << name << std::endl; }),
                MakeAnd(
                    graphics_.VehicleRideVertex(*veh.ptr, end_info.ptr->GetName()),
                    veh.ptr->Visit(*end_info.ptr)
                    ),
                Callback([vehicle_name = veh.ptr->GetName(),
                          &vehicles_ = vehicles_, this, id]()
                {
                    auto& info = vehicles_.at(vehicle_name);
                    info.current_vertex = id;
                    Route(info);
                })
                ));
    }

    ProcessPtr Simulation::Ride(VehicleInfo& veh, VertexInfo& from, VertexInfo& to)
    {
        double time_on_road =
            graph_.GetEdgeWeight(from.graph_id, to.graph_id) / veh.ptr->GetSpeed();
        /*graph_.Get(from.graph_id, to.graph_id) / veh.ptr->GetSpeed()*/
        return graphics_.VehicleRideRoad(*veh.ptr,
                                         from.ptr->GetName(),
                                         to.ptr->GetName(),
                                         time_on_road);
    }

    ProcessPtr Simulation::PassAndRide(VehicleInfo& veh, VertexInfo& from, VertexInfo& to)
    {
        double time_on_road =
            graph_.GetEdgeWeight(from.graph_id, to.graph_id) / veh.ptr->GetSpeed();

        return ToPtr(MakeConsecutive(
                         MakeAnd(
                             veh.ptr->Pass(*from.ptr),
                             graphics_.VehicleRideVertex(*veh.ptr, from.ptr->GetName())
                             ),
                         graphics_.VehicleRideRoad(*veh.ptr,
                                                   from.ptr->GetName(),
                                                   to.ptr->GetName(),
                                                   time_on_road)
                         )
            );
    }
}
