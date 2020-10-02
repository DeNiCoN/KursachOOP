#pragma once
#include <nlohmann/json.hpp>
#include <memory>
#include <iostream>

namespace Transport
{
    class Road
    {
    public:
        virtual void parse(const nlohmann::json&) = 0;

    };

    using RoadPtr = std::unique_ptr<Road>;
}
