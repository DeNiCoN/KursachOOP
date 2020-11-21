#pragma once
#include <nlohmann/json.hpp>
#include "graphics.hpp"
#include "simulation.hpp"
#include "renderer.hpp"
#include "factories.hpp"
#include "process_manager.hpp"

namespace transport
{
    class Application
    {
    public:

        Application(const nlohmann::json& vertices);
        void LoadVehicles(const nlohmann::json& vehicles);

        int Start();
    private:
        Renderer renderer_;
        Graphics graphics_;
        Simulation simulation_;
        ProcessManager p_manager_;
        VehicleFactory vehicle_factory_;
        VertexFactory vertex_factory_;
    };
}
