#pragma once
#include <nlohmann/json.hpp>
#include "graphics.hpp"
#include "process_manager.hpp"
#include "factories.hpp"
#include <unordered_map>

namespace transport
{
    class RouteInfo
    {
    public:
        std::string name;
        //Contains vehicle and vector of routes
    };

    /*
    ** Отвечает за считывание данных, и заполнение Graphics
    */
    class Frontend
    {
    public:
        Frontend(const nlohmann::json& routes, Graphics&);
        std::vector<ProcessPtr> generateProcesses(const nlohmann::json& vehicles) const;
    private:
        VehicleFactory m_vehicleFactory;
        VertexFactory m_vertexFactory;
        RoadFactory m_roadFactory;
        Graphics& m_graphics;
    };
}
