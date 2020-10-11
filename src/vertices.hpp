#pragma once
#include "vertex.hpp"
#include <iostream>

namespace Transport
{
    class TestVertex : public VertexBase
    {
    public:
        void visit(TestVehicle& veh) override
        {
            std::cout << "I hate second, but i love you!\n";
        }
        void parse(const nlohmann::json&) override {};
    };

    class SecondTestVertex : public VertexBase
    {
    public:
        void visit(SecondTestVehicle& vech) override
        {
            std::cout << "Hello second, i love you!\n";
        }
        void parse(const nlohmann::json&) override {};
    };
}
