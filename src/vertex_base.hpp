#pragma once
#include "vertex.hpp"
#include "vehicles.hpp"

namespace transport
{
    template<class T>
    struct VertexBaseSingle : public virtual Vertex
    {
        using Vertex::Visit;
        using Vertex::Pass;
        ProcessPtr Visit(T& t) override { return VisitDefault(t); }
        ProcessPtr Pass(T& t) override { return PassDefault(t); }
    };

    template<class... T>
    struct VertexBaseMultiple : VertexBaseSingle<T>...
    {
        using VertexBaseSingle<T>::Visit...;
    };

    struct VertexBase : VertexBaseMultiple<
        vehicles::Light,
        vehicles::Truck,
        vehicles::Passenger,
        vehicles::IllegalRacer,
        vehicles::Colorful,
        vehicles::Police,
        vehicles::Tractor
        >
    {};
}
