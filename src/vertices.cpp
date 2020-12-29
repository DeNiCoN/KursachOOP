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
            veh.SetAcceleration(1.5);
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

        ProcessPtr BusStop::Visit(vehicles::IllegalRacer& veh)
        {
            veh.SetAcceleration(1.);
            return std::make_unique<Wait>(0.);
        }
        ProcessPtr BusStop::Pass(vehicles::IllegalRacer& veh)
        {
            veh.SetAcceleration(1.);
            return std::make_unique<Wait>(0.);
        }

        const Renderer::TextureHandle BusStop::GetTexture() const
        {
            static auto texture = TextureLoader::Load("textures/bus_stop.png");
            return texture;
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
            double len = crops_;
            double speed = crops_ / veh.GetStuffPerTick();
            return ToPtr(InterpolateCallback(speed, [this, from, len](double t)
            {
                stuff_ = from + len * t;
                crops_ = len * std::abs(1. - t);
            }));
        }

        ProcessPtr Field::Visit(vehicles::Truck& veh)
        {
            double from = veh.GetLoaded();
            double len = stuff_;
            return ToPtr(InterpolateCallback(5. * len, [this, &veh, from, len](double t)
            {
                stuff_ = len * std::abs(1. - t);
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



        ProcessPtr Factory::Visit(vehicles::Truck& veh)
        {
            double from = veh.GetLoaded();
            double to = std::min(veh.GetMaxCapacity(), stuff_);
            double stuff_current = stuff_;
            if (from > 0.1)
            {
                return ToPtr(InterpolateCallback(std::abs(from * 4), [&veh, this, from](double t)
                {
                    veh.SetLoaded(std::abs(from - from * t));
                    materials_ = from * t;
                }));
            }
            else
            {
                return ToPtr(InterpolateCallback(std::abs(from * 4), [&veh, this, to, stuff_current](double t)
                {
                    veh.SetLoaded(to * t);
                    stuff_ -= stuff_current - to * t;
                }));
            }
        }

        const Renderer::TextureHandle Factory::GetTexture() const
        {
            static auto texture = TextureLoader::Load("textures/factory.png");
            if (materials_ > 0.1)
            {
                materials_ -= 0.1;
                stuff_ += 0.05;
            }
            return texture;
        }



        ProcessPtr ConstructionSite::Visit(vehicles::Truck& veh)
        {
            double from = veh.GetLoaded();
            return ToPtr(InterpolateCallback(std::abs(from * 4), [&veh, this, from](double t)
            {
                veh.SetLoaded(std::abs(from - from * t));
                materials_ = from * t;
            }));
        }

        const Renderer::TextureHandle ConstructionSite::GetTexture() const
        {
            static std::vector<Renderer::TextureHandle> textures =
            {
                TextureLoader::Load("textures/construction0.png"),
                TextureLoader::Load("textures/construction1.png"),
                TextureLoader::Load("textures/construction2.png"),
                TextureLoader::Load("textures/construction3.png"),
                TextureLoader::Load("textures/construction4.png"),
                TextureLoader::Load("textures/construction5.png"),
                TextureLoader::Load("textures/construction6.png")
            };

            if (materials_ > 0.01 && build_progress_ < build_end_)
            {
                materials_ -= 0.01;
                build_progress_ += 0.005;
            }

            return textures[6. * build_progress_ / build_end_];
        }

    }
}
