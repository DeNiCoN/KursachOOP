#pragma once
#include <nlohmann/json.hpp>
#include "vechicle_factory.hpp"
#include "process_manager.hpp"
#include <unordered_map>

namespace Transport
{
    class RouteInfo
    {
    public:
        std::string name;
        //Contains vechicle and vector of routes
    };

    class Frontend
    {
    public:
        Frontend(const nlohmann::json& routes);
        std::vector<ProcessPtr> generateProcesses(const nlohmann::json& vechicles) const;

    private:
        VechicleFactory m_vechicleFactory;
    };
}
