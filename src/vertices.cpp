#include "vertices.hpp"
#include "processes.hpp"
#include <glm/gtc/random.hpp>

namespace transport
{
    namespace vertices
    {
        using namespace processes;

        ProcessPtr Basic::VisitDefault(Vehicle& veh)
        {
            return std::make_unique<Wait>(wait_time_);
        }

        ProcessPtr Basic::PassDefault(Vehicle& veh)
        {
            return std::make_unique<Wait>(pass_time_);
        }

        ProcessPtr Recolor::Visit(vehicles::Colorful& veh)
        {
            auto color = glm::linearRand(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
            auto init = veh.GetColor();
            auto to = color - init;
            return ToPtr(InterpolateCallback(recolor_time_, [init, to, &veh](float t)
            {
                veh.SetColor(init + to * t);
            }));
        }

        ProcessPtr Police::Pass(vehicles::IllegalRacer& veh)
        {
            veh.SetAcceleration(2.);
            return std::make_unique<Wait>(pass_time_);
        }

        ProcessPtr Police::Visit(vehicles::IllegalRacer& veh)
        {
            veh.SetAcceleration(2.);
            return std::make_unique<Wait>(wait_time_);
        }

        void Police::Parse(const nlohmann::json& json)
        {
            if (json.contains("wait_time"))
                wait_time_ = json["wait_time"];
            if (json.contains("pass_time"))
                pass_time_ = json["pass_time"];
        }

        std::vector<VertexType> Police::GetTypes()
        {
            return { VertexType::POLICE };
        }

        const Renderer::TextureHandle Police::GetTexture() const
        {
            static auto texture = TextureLoader::Load("textures/police_station.png");
            return texture;
        }

        ProcessPtr BusStop::Visit(vehicles::Passenger& veh)
        {
            double from = veh.GetPassenger();
            double to = ((rand() % 100) / 100.0) * veh.GetMaxPassenger();
            double len = to - from;
            return ToPtr(InterpolateCallback(std::abs(len*4.0), [&veh, from, len](double t)
            {
                veh.SetPassenger(from + t * len);
            }));
        }
    }
}
