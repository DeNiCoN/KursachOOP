#pragma once
#include "nlohmann/json.hpp"
#include <memory>

namespace Transport
{
    class TestVehicle;
    class SecondTestVehicle;

    class Vertex
    {
    public:
        virtual void visit(TestVehicle&) = 0;
        virtual void visit(SecondTestVehicle&) = 0;
        virtual void parse(const nlohmann::json&) = 0;
    };

    using VertexPtr = std::unique_ptr<Vertex>;

    template<class T>
    struct VertexBase_single : public virtual Vertex
    {
        using Vertex::visit;
        void visit(T&) override {}
    };

    template<class... T>
    struct VertexBase_multiple : VertexBase_single<T>...
    {
        using VertexBase_single<T>::visit...;
    };

    struct VertexBase : VertexBase_multiple<
        TestVehicle, SecondTestVehicle
        >
    {};
}
