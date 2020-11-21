#pragma once
#include "vertex.hpp"
#include <iostream>

namespace transport
{
    class TestVertex : public VertexBase
    {
    public:
        double Visit(TestVehicle& veh) override
        {
            std::cout << "I hate second, but i love you!\n";
            return 0.;
        }
        void Parse(const nlohmann::json&) override {};
        const Renderer::Texture& GetTexture() override { return {}; }
    };

    class SecondTestVertex : public VertexBase
    {
    public:
        double Visit(SecondTestVehicle& vech) override
        {
            std::cout << "Hello second, i love you!\n";
            return 100.;
        }
        void Parse(const nlohmann::json&) override {};
        const Renderer::Texture& GetTexture() override { return {}; }
    };
}
