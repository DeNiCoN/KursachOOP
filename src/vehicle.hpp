#pragma once
#include "vertex.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <iostream>

namespace Transport
{
    class Vehicle
    {
    public:
        virtual void accept(Vertex&) = 0;
        virtual void parse(const nlohmann::json&) = 0;
    };

    using VehiclePtr = std::unique_ptr<Vehicle>;

    template<typename Veh>
    class VehicleBase : public Vehicle
    {
    public:
        void accept(Vertex& vert) override
        {
            vert.visit(*static_cast<Veh*>(this));
        }
    };
}
