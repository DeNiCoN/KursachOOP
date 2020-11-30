#pragma once
#include "factory_base.hpp"
#include "vehicle.hpp"
#include "vertex.hpp"
#include "roads.hpp"

namespace transport
{
    using VehicleFactory = FactoryBase<Vehicle>;
    using VertexFactory = FactoryBase<Vertex>;
}
