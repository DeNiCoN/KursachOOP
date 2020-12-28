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

        ProcessPtr PoliceVert::Pass(vehicles::IllegalRacer& veh)
        {
            veh.SetAcceleration(2.);
            return std::make_unique<Wait>(pass_time_);
        }

        ProcessPtr PoliceVert::Visit(vehicles::IllegalRacer& veh)
        {
            veh.SetAcceleration(2.);
            return std::make_unique<Wait>(wait_time_);
        }

        void PoliceVert::Parse(const nlohmann::json& json)
        {
            if (json.contains("wait_time"))
                wait_time_ = json["wait_time"];
            if (json.contains("pass_time"))
                pass_time_ = json["pass_time"];
        }

        std::vector<VertexType> PoliceVert::GetTypes()
        {
            return { VertexType::POLICE };
        }

        const Renderer::TextureHandle PoliceVert::GetTexture() const
        {
            static auto texture = TextureLoader::Load("textures/police_vert.png");
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

        void GasStation::Parse(const nlohmann::json& json)
        {
            if (json.contains("wait_time"))
                wait_time_ = json["wait_time"];
        }

        ProcessPtr GasStation::VisitDefault(Vehicle& veh)
        {
            return std::make_unique<Wait>(wait_time_);
        }

        void Field::Parse(const nlohmann::json& json)
        {
            if (json.contains("max_cappasity"))
                max_cappasity_ = json["max_cappasity"];
        }

        const Renderer::TextureHandle Field::GetTexture() const
        {
            static const std::vector<Renderer::TextureHandle> textures
            {
                TextureLoader::Load("textures/field0.png"),
                TextureLoader::Load("textures/field1.png"),
                TextureLoader::Load("textures/field2.png"),
                TextureLoader::Load("textures/field3.png"),
                TextureLoader::Load("textures/field4.png"),
                TextureLoader::Load("textures/field5.png")
            };
            crops_ += 1.0/60.0 * 0.02;
            if (crops_ > max_cappasity_)
                crops_ = max_cappasity_;
            return textures[5 * crops_ / max_cappasity_];
        }

        ProcessPtr Field::Visit(vehicles::Tractor& veh)
        {
            double from = stuff_;
            double replenishment = crops_;
            return ToPtr(InterpolateCallback(10. * replenishment, [this, from, replenishment](double t)
            {
                stuff_ = from + replenishment * t;
                crops_ = from * (1. - t);
            }));
        }

        ProcessPtr Field::Visit(vehicles::Truck& veh)
        {
            double from = veh.GetLoaded();
            double len = stuff_;
            return ToPtr(InterpolateCallback(5. * len, [this, &veh, from, len](double t)
            {
                stuff_ = len * (1. - t);
                veh.SetLoaded(from + len * t);
            }));
        }

        ProcessPtr Warehouse::Visit(vehicles::Truck& veh)
        {
            double from = veh.GetLoaded();
            double len = veh.GetMaxCapacity() - from;
            return ToPtr(InterpolateCallback(5. * len, [&veh, from, len](double t)
            {
                veh.SetLoaded(from + len * t);
            }));
        }

        const Renderer::TextureHandle Warehouse::GetTexture() const
        {
            static auto texture = TextureLoader::Load("textures/warehouse.png");
            return texture;
        }

    }
}
