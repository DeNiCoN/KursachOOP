#pragma once
#include <nlohmann/json.hpp>
#include <iostream>

namespace Transport
{
    class Vechicle
    {
    public:
        virtual void Parse(const nlohmann::json&) = 0;
    };

    class TestVechicle : public Vechicle
    {
    public:
        void Parse(const nlohmann::json&) { std::cout << "Imagine parsing\n"; }
    };
}
