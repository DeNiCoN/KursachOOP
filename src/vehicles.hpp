#pragma once
#include "vehicle.hpp"
#include "glm/vec4.hpp"
#include <cstdlib>

namespace transport
{
    namespace vehicles
    {
        class Light : public VehicleBase<Light>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::TextureHandle GetTexture() const override;
            double GetSpeed() const override; 
            void SetSpeed(const int speed);
        private:
            double max_speed_ = 1.;
        };

        class Truck : public VehicleBase<Truck>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::TextureHandle GetTexture() const override;
            double GetSpeed() const override;
            void SetLoaded(const double cargo_mass);
        private:
            double max_speed_ = 1.;
            double loaded_ = 0.;
            double max_carrying_capacity_ = 1.;
        };

        class Passenger : public VehicleBase<Passenger>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::TextureHandle GetTexture() const override;
            double GetSpeed() const override;
            double GetMaxPassenger() const { return max_passenger_; }
            double GetPassenger() const { return passenger_; }
            void SetPassenger(double pass) { passenger_ = pass; }
            std::optional<VertexType> GetNextVertexType() const override
            { return VertexType::BUS_STOP; }
        private:
            double max_speed_ = 1.;
            double passenger_ = 0.;
            double max_passenger_ = 1.;
        };

        class IllegalRacer : public Light
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::TextureHandle GetTexture() const override;
            double GetSpeed() const override;
            void SetAcceleration(const double acceleration);

            ProcessPtr Visit(Vertex& vert) override {return vert.Visit(*this);}
            ProcessPtr Pass(Vertex& vert) override {return vert.Pass(*this);}
        private:
            double acceleration_ = 1.;
        };

        class Colorful: public Light
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::TextureHandle GetTexture() const override;
            glm::vec3 GetColor() const override;
            void SetColor(const glm::vec3 color);

            ProcessPtr Visit(Vertex& vert) override {return vert.Visit(*this);}
            ProcessPtr Pass(Vertex& vert) override {return vert.Pass(*this);}

        private:
            glm::vec3 color_ = {1.f, 1.f, 1.f};
        };

        class Police: public Light
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::TextureHandle GetTexture() const override;
            double GetSpeed() const override;

            ProcessPtr Visit(Vertex& vert) override {return vert.Visit(*this);}
            ProcessPtr Pass(Vertex& vert) override {return vert.Pass(*this);}
        private:
        };

        class Tractor : public VehicleBase<Tractor>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::TextureHandle GetTexture() const override;
            double GetSpeed() const override;
            void SetStuffPerTick(const double stuff_per_tick);  //how much tractor can produce per tick
        private:
            double max_speed_ = 1.;
            double stuff_per_tick_ = 1.;
        };

    }
}
