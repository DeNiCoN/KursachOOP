#pragma once
#include "vertex.hpp"
#include <iostream>

namespace transport
{
    class TestVertex : public VertexBase
    {
    public:
        void Visit(TestVehicle& veh) override
        {
            std::cout << "I hate second, but i love you!\n";
        }
        void Parse(const nlohmann::json&) override {};
    };

    class SecondTestVertex : public VertexBase
    {
    public:
        void Visit(SecondTestVehicle& vech) override
        {
            std::cout << "Hello second, i love you!\n";
        }
        void Parse(const nlohmann::json&) override {};
    };
}
