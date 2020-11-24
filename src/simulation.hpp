#pragma once
#include "graphics.hpp"
#include "graph.hpp"
#include "router.hpp"
#include <unordered_map>

namespace transport
{
    class Simulation
    {
    public:
        Simulation(Graphics& graphics, ProcessManager& p_manager);
        void AddVehicle(VehiclePtr vehicle_ptr, std::string start_position);
        void AddVertex(VertexPtr vertex_ptr);
        void AddRoad(std::string from, std::string to, double length);

    private:
        Graphics& graphics_;
        ProcessManager& p_manager_;
        Graph graph_;

        struct VertexInfo
        {
            VertexPtr ptr;
            //TODO change to VertexId
            int graph_id;
        };

        struct VehicleInfo
        {
            VehiclePtr ptr;
            std::string current_vertex;
        };

        std::unordered_map<std::string, VehicleInfo> vehicles_;
        std::unordered_map<std::string, VertexInfo> vertices_;
    };
}
