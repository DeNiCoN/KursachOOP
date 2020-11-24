#pragma once
#include "vertex_base.hpp"
#include <iostream>

namespace transport
{
    class TestVertex : public VertexBase
    {
    public:
        ProcessPtr Visit(TestVehicle& veh) override
        {
            return nullptr;
        }
        void Parse(const nlohmann::json&) override {};
        const Renderer::Texture& GetTexture() override { return {}; }
    };

    class SecondTestVertex : public VertexBase
    {
    public:
        ProcessPtr Visit(SecondTestVehicle& vech) override
        {
            return nullptr;
        }
        void Parse(const nlohmann::json&) override {};
        const Renderer::Texture& GetTexture() override { return {}; }
    };
}
