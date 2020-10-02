#include "factories.hpp"
#include "vechicles.hpp"
#include "vertices.hpp"

namespace Transport
{
    template<>
    const std::unordered_map<std::string,
                             std::function<VechiclePtr()>
                             > VechicleFactory::s_typeToObj
    {
        TYPE_TO_OBJ_NODE(TestVechicle),
        TYPE_TO_OBJ_NODE(SecondTestVechicle)
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
