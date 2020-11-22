#pragma once
#include "vertex.hpp"
#include "vehicles.hpp"

namespace transport
{
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
