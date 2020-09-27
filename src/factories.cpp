#include "factories.hpp"

namespace Transport
{
    template<>
    const std::unordered_map<std::string,
                             std::function<VechiclePtr()>
                             > VechicleFactory::s_typeToObj
    {
        TYPE_TO_OBJ_NODE(TestVechicle)
    };

    template<>
    const std::unordered_map<std::string,
                             std::function<VertexPtr()>
                             > VertexFactory::s_typeToObj
    {
    };

    template<>
    const std::unordered_map<std::string,
                             std::function<RoadPtr()>
                             > RoadFactory::s_typeToObj
    {
    };
}
