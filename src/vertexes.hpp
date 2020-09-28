#pragma once

#include <nlohmann/json.hpp>
#include <memory>
#include <iostream>

namespace Transport
{
    class Vertex
    {
    public:
        virtual void Parse(const nlohmann::json&) = 0;

    };

    using VertexPtr = std::unique_ptr<Vertex>;
}
