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
                if (json.contains("wait_time"))
                    wait_time_ = json["wait_time"];
                if (json.contains("pass_time"))
                    pass_time_ = json["pass_time"];
            };

            const Renderer::TextureHandle GetTexture() const override
            {
                static auto texture = TextureLoader::Load("textures/basic.png");
                return texture;
            }

        private:
            double wait_time_ = 1.;
            double pass_time_ = 0.;
        };

        class Recolor : public VertexBase
        {
        public:
            //Only does something with colorful, ignores other
            ProcessPtr Visit(vehicles::Colorful& veh) override;
            void Parse(const nlohmann::json& json) override
            {
                if (json.contains("recolor_time"))
                    recolor_time_ = json["recolor_time"];
                //No arguments
            };

            std::vector<VertexType> GetTypes() override
            {
                return { VertexType::RECOLOR };
            }

            const Renderer::TextureHandle GetTexture() const override
            {
                static auto texture = TextureLoader::Load("textures/recolor.png");
                return texture;
            }

        private:
            double recolor_time_ = 1.;
        };

        class Police : public VertexBase
        {
        public:
            ProcessPtr Visit(vehicles::IllegalRacer& veh) override;
            ProcessPtr Pass(vehicles::IllegalRacer& veh) override;
            void Parse(const nlohmann::json& json) override;
            std::vector<VertexType> GetTypes() override;
            const Renderer::TextureHandle GetTexture() const override;
        private:
            double pass_time_ = 0.;
            double wait_time_ = 0.;
        };

        class BusStop : public VertexBase
        {
        public:
            ProcessPtr Visit(vehicles::Passenger& veh) override;
            void Parse(const nlohmann::json& json) override {}

            std::vector<VertexType> GetTypes() override
            {
                return { VertexType::BUS_STOP };
            }

            const Renderer::TextureHandle GetTexture() const override
            {
                static auto texture = TextureLoader::Load("textures/bus_stop.png");
                return texture;
            }
        };
    }
}
