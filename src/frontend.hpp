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
        std::vector<ProcessPtr> GenerateProcesses(const nlohmann::json& vehicles) const;
    private:
        VehicleFactory vehicle_factory_;
        VertexFactory vertex_factory_;
        Graphics& graphics_;
    };
}
