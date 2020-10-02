#pragma once
#include "nlohmann/json.hpp"
#include <memory>

namespace Transport
{
    class TestVechicle;
    class SecondTestVechicle;

    class Vertex
    {
    public:
        virtual void visit(TestVechicle&) = 0;
        virtual void visit(SecondTestVechicle&) = 0;
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
        TestVechicle, SecondTestVechicle
        >
    {};
}
