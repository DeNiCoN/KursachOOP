#pragma once
#include "factory_base.hpp"
#include "vechicles.hpp"
#include "vertexes.hpp"
#include "roads.hpp"

namespace Transport
{
    using VechicleFactory = FactoryBase<Vechicle>;
    using VertexFactory = FactoryBase<Vertex>;
    using RoadFactory = FactoryBase<Road>;
}
