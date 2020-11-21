#pragma once
#include "vehicle.hpp"

namespace transport
{
    class TestVehicle : public VehicleBase<TestVehicle>
    {
        void Parse(const nlohmann::json&) override {};
        const Renderer::Texture& GetTexture() override { return {}; }
    };

    class SecondTestVehicle : public VehicleBase<SecondTestVehicle>
    {
        void Parse(const nlohmann::json&) override {};
        const Renderer::Texture& GetTexture() override { return {}; }
    };
}
