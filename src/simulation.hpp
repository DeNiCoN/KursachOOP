#pragma once
#include "graphics.hpp"
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

        std::unordered_map<std::string, VehiclePtr> vehicles_;
        std::unordered_map<std::string, VertexPtr> vertices_;

    };
}
