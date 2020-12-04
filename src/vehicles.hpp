#pragma once
#include "vehicle.hpp"
#include "glm/vec4.hpp"

namespace transport
{
    namespace vehicles
    {
        class Light : public VehicleBase<Light>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() const override;
            double GetSpeed() const override; 
            void SetSpeed(const int speed);
        private:
            double max_speed_ = 1.;
        };

        class Truck : public VehicleBase<Truck>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() const override;
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
            const Renderer::Texture& GetTexture() const override;
            double GetSpeed() const override;
            void AddPassenger(const int passenger_quan);
            void SubtractPassenger(const int passenger_qua);
        private:
            double max_speed_ = 1.;
            int passenger_ = 0;
            int max_passenger_ = 1;
        };

        class IllegalRacer : public Light
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() const override;
            double GetSpeed() const override;
            void SetAcceleration(const double acceleration);
        private:
            double acceleration_ = 1.;
        };

        class Colorful: public Light
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() const override;
            double GetSpeed() const override;
            void SetColor(const glm::vec4 color);
        private:
            glm::vec4 color_ = {0., 0., 0., 0.};
        };

        class Police: public Light
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() const override;
            double GetSpeed() const override;
        private:
        };

        class Tractor : public VehicleBase<Tractor>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() const override;
            double GetSpeed() const override;
            void SetStuffPerTick(const double stuff_per_tick);  //how much tractor can produce per tick
        private:
            double max_speed_ = 1.;
            double stuff_per_tick_ = 1.;
        };

    }
}
