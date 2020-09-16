#pragma once
#include <nlohmann/json.hpp>
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
        std::vector<RouteInfo> generate(const nlohmann::json& vechicles) const;
    };
}
