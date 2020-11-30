#include "factories.hpp"
#include "vehicles.hpp"
#include "vertices.hpp"

namespace transport
{
    using namespace vertices;
    using namespace vehicles;

    template<>
    const std::unordered_map<std::string,
                             std::function<VehiclePtr()>
                             > VehicleFactory::type_to_obj_
    {
        TYPE_TO_OBJ_NODE(Light)
    };

    template<>
    const std::unordered_map<std::string,
                             std::function<VertexPtr()>
                             > VertexFactory::type_to_obj_
    {
        TYPE_TO_OBJ_NODE(Basic)
    };
}
