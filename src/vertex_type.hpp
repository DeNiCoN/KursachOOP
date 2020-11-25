#pragma once

namespace transport
{
    enum class VertexType
    {
        DEFAULT,
        RECOLOR,
        POLICE,
        FACTORY,
        BUS_STOP,
        CONSTRUCTION_SITE,
        GAS_STATION,
        FIELD,
        WAREHOUSE,
        LAST    // Must always be last, used only to count amount of enum elements. LAST is NOT type of vertex.
    };
}
