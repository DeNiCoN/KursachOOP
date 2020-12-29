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

        class PoliceVert : public VertexBase
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
            ProcessPtr Visit(vehicles::IllegalRacer& veh) override;
            ProcessPtr Pass(vehicles::IllegalRacer& veh) override;
            void Parse(const nlohmann::json& json) override {}
            const Renderer::TextureHandle GetTexture() const override;
            std::vector<VertexType> GetTypes() override
            {
                return { VertexType::BUS_STOP };
            }
        };

        class ConstructionSite : public VertexBase
        {
        public:
            ProcessPtr Visit(vehicles::Truck& veh) override;
            void Parse(const nlohmann::json& json) {};
            const Renderer::TextureHandle GetTexture() const override;
            std::vector<VertexType> GetTypes() override
            {
                return { VertexType::CONSTRUCTION_SITE, VertexType::DROP_CARGO };
            }

        private:
            mutable double materials_ = 0.;
            mutable double build_progress_ = 0.;
            double build_end_ = 10.;
        };

        class GasStation : public VertexBase
        {
        public:
            ProcessPtr VisitDefault(Vehicle& veh) override;
            void Parse(const nlohmann::json& json);

            std::vector<VertexType> GetTypes() override
            {
                return { VertexType::GAS_STATION };
            }

            const Renderer::TextureHandle GetTexture() const override
            {
                static auto texture = TextureLoader::Load("textures/gas_station.png");
                return texture;
            }
        private:
            double wait_time_ = 1.;
        };

        class Field : public VertexBase
        {
        public:
            ProcessPtr Visit(vehicles::Tractor& veh) override;
            ProcessPtr Visit(vehicles::Truck& veh) override;
            void Parse(const nlohmann::json& json);
            const Renderer::TextureHandle GetTexture() const override;
            std::vector<VertexType> GetTypes() override
            {
                return { VertexType::FIELD, VertexType::PICK_UP_CARGO };
            }

        private:
            mutable double crops_ = 0.;             //how much crops have grown, idk. How much tractor can transform into stuff/supplies
            double max_cappasity_ = 1.;     //how much crops can be. Max value for crops
            double stuff_ = 0.;             //crops transformed into stuff. Infinity storage. Something that truck takes
        };

        class Warehouse : public VertexBase
        {
        public:
            ProcessPtr Visit(vehicles::Truck& veh) override;
            void Parse(const nlohmann::json& json) {};
            const Renderer::TextureHandle GetTexture() const override;
            std::vector<VertexType> GetTypes() override
            {
                return { VertexType::WAREHOUSE, VertexType::PICK_UP_CARGO };
            }
        };

        class Factory : public VertexBase
        {
        public:
            ProcessPtr Visit(vehicles::Truck& veh) override;
            void Parse(const nlohmann::json& json) {};
            const Renderer::TextureHandle GetTexture() const override;
            std::vector<VertexType> GetTypes() override
            {
                return { VertexType::FACTORY, VertexType::DROP_CARGO, VertexType::PICK_UP_CARGO};
            }

        private:
            mutable double materials_ = 0.;
            mutable double stuff_ = 0.;
        };
    }
}
