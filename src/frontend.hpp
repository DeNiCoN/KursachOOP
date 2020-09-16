#pragma once
#include <nlohmann/json.hpp>

namespace Transport
{

    class Frontend
    {
    public:
        Frontend(nlohmann::json routes, nlohmann::json vechicles);
       
    };
}
