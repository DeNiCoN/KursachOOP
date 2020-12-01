#pragma once
#include "vehicle.hpp"

namespace transport
{
    namespace vehicles
    {
        class Light : public VehicleBase<Light>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() override;
            double GetSpeed() override; 
        private:
            double max_speed_ = 1.;
        };

        class Truck : public VehicleBase<Truck>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() override;
            double GetSpeed() override;     
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
            const Renderer::Texture& GetTexture() override;
            double GetSpeed() override;
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
            const Renderer::Texture& GetTexture() override;
            double GetSpeed() override;
            void SetAcceleration(const double acceleration);
        private:
            double max_speed_ = 1.;
            double acceleration_ = 1.;
        };

        class Colorful: public Light
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() override;
            double GetSpeed() override;
            void SetColor(const std::string color);
        private:
            double max_speed_ = 1.;
            std::string color_ = "#ffffff";
        };

        class Police: public Light
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() override;
            double GetSpeed() override;
        private:
            double max_speed_ = 1.;
        };

        class Tractor : public VehicleBase<Tractor>
        {
        public:
            void Parse(const nlohmann::json& json) override;
            const Renderer::Texture& GetTexture() override;
            double GetSpeed() override;
            void SetStuffPerTick(const double stuff_per_tick);  //how much tractor can produce per tick
        private:
            double max_speed_ = 1.;
            double stuff_per_tick_ = 1.;
        };

    }
}
