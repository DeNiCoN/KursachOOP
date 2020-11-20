#pragma once
#include "vertex.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <iostream>

namespace transport
{
    class Vehicle
    {
    public:
        virtual void Accept(Vertex&) = 0;
        virtual void Parse(const nlohmann::json&) = 0;
    };

    using VehiclePtr = std::unique_ptr<Vehicle>;

    template<typename Veh>
    class VehicleBase : public Vehicle
    {
    public:
        void Accept(Vertex& vert) override
        {
            vert.Visit(*static_cast<Veh*>(this));
        }
    };
}
