#include "factories.hpp"
#include "vehicles.hpp"
#include "vertices.hpp"

namespace transport
{
    template<>
    const std::unordered_map<std::string,
                             std::function<VehiclePtr()>
                             > VehicleFactory::s_typeToObj
    {
        TYPE_TO_OBJ_NODE(TestVehicle),
        TYPE_TO_OBJ_NODE(SecondTestVehicle)
    };

    template<>
    const std::unordered_map<std::string,
                             std::function<VertexPtr()>
                             > VertexFactory::s_typeToObj
    {
        TYPE_TO_OBJ_NODE(TestVertex),
        TYPE_TO_OBJ_NODE(SecondTestVertex)
    };

    template<>
    const std::unordered_map<std::string,
                             std::function<RoadPtr()>
                             > RoadFactory::s_typeToObj
    {
    };
}
