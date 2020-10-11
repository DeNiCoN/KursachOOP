#pragma once
#include "factory_base.hpp"
#include "vehicle.hpp"
#include "vertex.hpp"
#include "roads.hpp"

namespace Transport
{
    using VehicleFactory = FactoryBase<Vehicle>;
    using VertexFactory = FactoryBase<Vertex>;
    using RoadFactory = FactoryBase<Road>;
}
