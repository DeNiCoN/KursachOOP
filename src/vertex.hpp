#pragma once
#include "nlohmann/json.hpp"
#include <memory>
#include "json_deserializable.hpp"
#include "graphics_object.hpp"
#include "vertex_type.hpp"

namespace transport
{
    class Vehicle;
    class TestVehicle;
    class SecondTestVehicle;

    class Vertex : public JsonDeserializable, public GraphicsObject
    {
    public:
        virtual double VisitDefault(Vehicle&) { return 1.; }
        virtual double Visit(TestVehicle&) = 0;
        virtual double Visit(SecondTestVehicle&) = 0;
        const std::string& GetName() { return name_; }
        void SetName(const std::string& name) { name_ = name; }
        virtual std::vector<VertexType> GetTypes()
        {
            return { VertexType::DEFAULT };
        }
    private:
        std::string name_;
    };

    using VertexPtr = std::unique_ptr<Vertex>;

    template<class T>
    struct VertexBaseSingle : public virtual Vertex
    {
        using Vertex::Visit;
        double Visit(T& t) override { return VisitDefault(t); }
    };

    template<class... T>
    struct VertexBaseMultiple : VertexBaseSingle<T>...
    {
        using VertexBaseSingle<T>::Visit...;
    };

    struct VertexBase : VertexBaseMultiple<
        TestVehicle, SecondTestVehicle
        >
    {};
}
