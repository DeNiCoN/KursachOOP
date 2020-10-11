#pragma once
#include "vehicle.hpp"

namespace Transport
{
    class TestVehicle : public VehicleBase<TestVehicle>
    {
        void parse(const nlohmann::json&) override {};
    };

    class SecondTestVehicle : public VehicleBase<SecondTestVehicle>
    {
        void parse(const nlohmann::json&) override {};
    };
}
