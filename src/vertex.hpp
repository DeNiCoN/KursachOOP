#pragma once
#include "nlohmann/json.hpp"
#include <memory>

namespace transport
{
    class TestVehicle;
    class SecondTestVehicle;

    class Vertex
    {
    public:
        virtual void Visit(TestVehicle&) = 0;
        virtual void Visit(SecondTestVehicle&) = 0;
        virtual void Parse(const nlohmann::json&) = 0;
    };

    using VertexPtr = std::unique_ptr<Vertex>;

    template<class T>
    struct VertexBaseSingle : public virtual Vertex
    {
        using Vertex::Visit;
        void Visit(T&) override {}
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
