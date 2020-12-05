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
        void AddRoad(const std::string& from, const std::string& to, double length);

    private:
        Graphics& graphics_;
        ProcessManager& p_manager_;
        Graph graph_;
        RouterBreadthFS router_;

        struct VertexInfo
        {
            VertexPtr ptr;
            //TODO change to VertexId
            int graph_id;
        };

        struct VehicleInfo
        {
            VehiclePtr ptr;
            int current_vertex;
        };

        std::unordered_map<std::string, VehicleInfo> vehicles_;
        std::unordered_map<std::string, int> vertices_;
        std::unordered_map<int, VertexInfo> vertices_id;

        void Route(VehicleInfo&);

        ProcessPtr VisitAndLookNext(VehicleInfo& veh, VertexInfo& end);
        ProcessPtr Ride(VehicleInfo& veh, VertexInfo& from, VertexInfo& to);
        ProcessPtr PassAndRide(VehicleInfo& veh, VertexInfo& from, VertexInfo& to);
    };
}
