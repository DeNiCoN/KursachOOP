#pragma once
#include "vehicle.hpp"

namespace transport
{
    namespace vehicles
    {
        class Light : public VehicleBase<Light>
        {
        public:
            void Parse(const nlohmann::json& json) override
            {
                if (json.count("max_speed"))
                    max_speed_ = json["max_speed"];
            }
            const Renderer::Texture& GetTexture() override { return {}; }
            double GetSpeed() override { return max_speed_; }
        private:
            double max_speed_ = 1.;
        };
    }
}
