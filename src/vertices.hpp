#pragma once
#include "vertex_base.hpp"
#include <iostream>
#include "texture_loader.hpp"

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
                    pass_time_ = json["pass_time"];
            };

            const Renderer::TextureHandle GetTexture() const override
            { return TextureLoader::Load("textures/basic.png"); }

        private:
            double wait_time_ = 1.;
            double pass_time_ = 0.;
        };
    }
}
