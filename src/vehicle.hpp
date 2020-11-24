#pragma once
#include "vertex.hpp"
#include <string>
#include <nlohmann/json.hpp>
#include <memory>
#include <iostream>
#include "process_manager.hpp"
#include "json_deserializable.hpp"
#include "graphics_object.hpp"

namespace transport
{
    class Vehicle : public JsonDeserializable, public GraphicsObject
    {
    public:
        virtual ProcessPtr Accept(Vertex&) = 0;
        virtual double GetSpeed() { return 1.; }
        const std::string& GetName() const { return name_; }
        void SetName(const std::string& name) { name_ = name; }
    private:
        std::string name_;
    };

    using VehiclePtr = std::unique_ptr<Vehicle>;

    template<typename Veh>
    class VehicleBase : public Vehicle
    {
    public:
        ProcessPtr Accept(Vertex& vert) override
        {
            return vert.Visit(*static_cast<Veh*>(this));
        }
    };
}
