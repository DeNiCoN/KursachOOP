#pragma once
#include "nlohmann/json.hpp"
#include "process_manager.hpp"
#include <memory>
#include "json_deserializable.hpp"
#include "graphics_object.hpp"
#include "vertex_type.hpp"

namespace transport
{
    class Vehicle;
    namespace vehicles
    {
        class Light;
    }

    class Vertex : public JsonDeserializable, public GraphicsObject
    {
    public:
        //TODO change nullptr to None process
        virtual ProcessPtr VisitDefault(Vehicle&) { return nullptr; }
        virtual ProcessPtr PassDefault(Vehicle&) { return nullptr; }

        virtual ProcessPtr Visit(vehicles::Light&) = 0;
        virtual ProcessPtr Pass(vehicles::Light&) = 0;

        const std::string& GetName() const { return name_; }
        void SetName(const std::string& name) { name_ = name; }
        virtual std::vector<VertexType> GetTypes()
        {
            return {};
        }
    private:
        std::string name_;
    };

    using VertexPtr = std::unique_ptr<Vertex>;

}
