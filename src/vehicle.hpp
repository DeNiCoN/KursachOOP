#pragma once
#include "vertex.hpp"
#include <string>
#include <nlohmann/json.hpp>
#include <memory>
#include <iostream>
#include "process_manager.hpp"
#include "json_deserializable.hpp"
#include "graphics_object.hpp"
#include <optional>

namespace transport
{
    class Vehicle : public JsonDeserializable, public GraphicsObject
    {
    public:
        virtual ProcessPtr Visit(Vertex&) = 0;
        virtual ProcessPtr Pass(Vertex&) = 0;
        virtual double GetSpeed() const { return 1.; }
        virtual std::optional<VertexType> GetNextVertexType() const { return std::nullopt; }
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
        ProcessPtr Visit(Vertex& vert) override
        {
            return vert.Visit(*static_cast<Veh*>(this));
        }

        ProcessPtr Pass(Vertex& vert) override
        {
            return vert.Pass(*static_cast<Veh*>(this));
        }
    };
}
