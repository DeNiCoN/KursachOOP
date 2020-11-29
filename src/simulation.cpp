#include "simulation.hpp"

namespace transport
{
    Simulation::Simulation(Graphics& graphics, ProcessManager& p_manager)
        : graphics_(graphics), p_manager_(p_manager), graph_(100000)
    {

    }

    void Simulation::AddVehicle(VehiclePtr vehicle_ptr, std::string start_position)
    {
        auto& info = vehicles_[vehicle_ptr->GetName()];
        info.ptr = std::move(vehicle_ptr);
        info.current_vertex = start_position;

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

    void Simulation::Process(VehicleInfo& info)
    {

    }
}
