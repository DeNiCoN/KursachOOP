#pragma once
#include "vertex.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <iostream>

namespace Transport
{
    class Vechicle
    {
    public:
        virtual void accept(Vertex&) = 0;
        virtual void parse(const nlohmann::json&) = 0;
    };

    using VechiclePtr = std::unique_ptr<Vechicle>;

    template<typename Vech>
    class VechicleBase : public Vechicle
    {
    public:
        void accept(Vertex& vert) override
        {
            vert.visit(*static_cast<Vech*>(this));
        }
    };
}
