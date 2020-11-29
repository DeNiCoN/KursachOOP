#pragma once
#include "vertex_base.hpp"
#include <iostream>

namespace transport
{
    namespace vertices
    {
        class Basic : public VertexBase
        {
        public:
            ProcessPtr VisitDefault(Vehicle& veh) override;
            ProcessPtr PassDefault(Vehicle& veh) override;
            void Parse(const nlohmann::json& json) override
            {
                if (json.count("wait_time"))
                    wait_time_ = json["wait_time"];
                if (json.count("pass_time"))
                    wait_time_ = json["pass_time"];
            };
            const Renderer::Texture& GetTexture() override { return {}; }
        private:
            double wait_time_ = 1.;
            double pass_time_ = 0.;
        };
    }
}
