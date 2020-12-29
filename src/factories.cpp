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
        TYPE_TO_OBJ_NODE(Light),
        TYPE_TO_OBJ_NODE(Truck),
        TYPE_TO_OBJ_NODE(Colorful),
        TYPE_TO_OBJ_NODE(Passenger),
        TYPE_TO_OBJ_NODE(IllegalRacer),
        TYPE_TO_OBJ_NODE(Police),
        TYPE_TO_OBJ_NODE(Tractor)
    };

    template<>
    const std::unordered_map<std::string,
                             std::function<VertexPtr()>
                             > VertexFactory::type_to_obj_
    {
        TYPE_TO_OBJ_NODE(Basic),
        TYPE_TO_OBJ_NODE(Recolor),
        TYPE_TO_OBJ_NODE(BusStop),
        TYPE_TO_OBJ_NODE(PoliceVert),
        TYPE_TO_OBJ_NODE(GasStation),
        TYPE_TO_OBJ_NODE(Field),
        TYPE_TO_OBJ_NODE(Warehouse),
        TYPE_TO_OBJ_NODE(Factory),
        TYPE_TO_OBJ_NODE(ConstructionSite)
    };
}
