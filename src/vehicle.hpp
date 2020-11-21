#pragma once
#include "vertex.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <iostream>
#include "json_deserializable.hpp"
#include "graphics_object.hpp"

namespace transport
{
    class Vehicle : public JsonDeserializable, public GraphicsObject
    {
    public:
        virtual void Accept(Vertex&) = 0;
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
