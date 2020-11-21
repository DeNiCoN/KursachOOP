#pragma once
#include <nlohmann/json.hpp>

namespace transport
{
    class JsonDeserializable
    {
    public:
        virtual void Parse(const nlohmann::json& ) = 0;
        virtual ~JsonDeserializable() = default;
    };
}
