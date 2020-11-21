#pragma once
#include "graphics.hpp"

namespace transport
{
    class Simulation
    {
    public:
        Simulation(Graphics& graphics, ProcessManager& p_manager);
        void AddVehicle(VehiclePtr vehicle_ptr, std::string start_position);
        void AddVertex(VertexPtr vertex_ptr);
        void AddRoad(std::string from, std::string to);

    private:
        Graphics& graphics_;
        ProcessManager& p_manager_;
    };
}
