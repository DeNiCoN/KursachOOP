#pragma once
#include <nlohmann/json.hpp>
#include "graphics.hpp"
#include "process_manager.hpp"
#include "factories.hpp"
#include <unordered_map>

namespace Transport
{
    class RouteInfo
    {
    public:
        std::string name;
        //Contains vechicle and vector of routes
    };

    /*
    ** Отвечает за считывание данных, и заполнение Graphics
    */
    class Frontend
    {
    public:
        Frontend(const nlohmann::json& routes, Graphics&);
        std::vector<ProcessPtr> generateProcesses(const nlohmann::json& vechicles) const;
    private:
        VechicleFactory m_vechicleFactory;
        Graphics& m_graphics;
    };
}
