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
        info.current_vertex = start_position;

        //Add simulation find route process
        //TODO add vehicles processes
    }

    void Simulation::AddVertex(VertexPtr vertex_ptr)
    {
        graphics_.AddVertex(vertex_ptr->GetName(), *vertex_ptr.get());

        auto& info = vertices_[vertex_ptr->GetName()];
        info.ptr = std::move(vertex_ptr);
        info.graph_id = graph_.AddVertex(info.ptr->GetTypes());
    }

    void Simulation::AddRoad(std::string from, std::string to, double length)
    {
        graphics_.AddRoad(from, to, length);

        graph_.AddEdge(vertices_.at(from).graph_id,
                       vertices_.at(to).graph_id, length);
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

        int current_id = vertices_.at(info.current_vertex).graph_id;
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
                auto next = PassAndRide(info, next_info, current_info);

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
        return make_unique<Consecutive>(
            And(
                graphics_.VehicleRideVertex(*veh.ptr, end_info.ptr->GetName()),
                veh.ptr->Visit(*end_info.ptr)
                ),
            Callback([vehicle_name = veh.ptr->GetName(),
                      &vehicles_ = vehicles_, this]()
            {
                Route(vehicles_.at(vehicle_name));
            })
            );
    }

    ProcessPtr Simulation::Ride(VehicleInfo& veh, VertexInfo& from, VertexInfo& to)
    {
        double time_on_road = 1.0 / veh.ptr->GetSpeed();
        /*graph_.GetWeight(route_queue[0], route_queue[1]) / info.ptr->GetSpeed()*/
        return graphics_.VehicleRideRoad(*veh.ptr,
                                         from.ptr->GetName(),
                                         to.ptr->GetName(),
                                         time_on_road);
    }

    ProcessPtr Simulation::PassAndRide(VehicleInfo& veh, VertexInfo& from, VertexInfo& to)
    {
        double time_on_road = 1.0 / veh.ptr->GetSpeed();

        return make_unique<Consecutive>(
            And(
                graphics_.VehicleRideVertex(*veh.ptr, from.ptr->GetName()),
                veh.ptr->Pass(*from.ptr)
                ),
            graphics_.VehicleRideRoad(*veh.ptr,
                                      from.ptr->GetName(),
                                      to.ptr->GetName(),
                                      time_on_road)
            );
    }
}
