#pragma once
#include "vechicle.hpp"

namespace Transport
{
    class TestVechicle : public VechicleBase<TestVechicle>
    {
        void parse(const nlohmann::json&) override {};
    };

    class SecondTestVechicle : public VechicleBase<SecondTestVechicle>
    {
        void parse(const nlohmann::json&) override {};
    };
}
