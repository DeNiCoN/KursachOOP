#pragma once
#include <nlohmann/json.hpp>
#include "vechicles.hpp"
#include <unordered_map>


namespace Transport
{
    using VechiclePtr = std::unique_ptr<Vechicle>;

    class VechicleFactory
    {
    public:
        VechiclePtr operator()(const nlohmann::json&) const;
        VechiclePtr operator()(const std::string&) const;
    private:
        static const std::unordered_map<std::string,
                                        std::function<std::unique_ptr<Vechicle>()>
                                        > s_typeToObj;
    };
}
