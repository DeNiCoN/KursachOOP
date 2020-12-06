#include "graphics.hpp"
#include "processes.hpp"
#include <glm/gtc/random.hpp>

namespace transport
{
    using namespace std;
    using namespace processes;

    Graphics::Graphics(Renderer& renderer, ProcessManager& p_manager)
        : renderer_(renderer), p_manager_(p_manager)
    {
        p_manager_.Add(ToPtr(WhileTrue([&](double delta)
        {
            float viscosity_damping = 2.f;
            float eps = 0.00000000001;
            for (auto& [name, vertex] : vertices_)
            {
                //Update position
                float spring_damping = 0.0001f;
                float spring_force = 10.f;

                glm::vec2 acceleration = {0.f, 0.f};
                for (const auto& [name, length] : vertex.incedent)
                {
                    const auto& incident = vertices_.at(name);
                    auto to = (incident.position - vertex.position);
                    if (glm::dot(to, to) < eps)
                    {
                        to = glm::circularRand(length/0.1f);
                    }
                    auto to_n = glm::normalize(to);
                    acceleration += static_cast<float>(spring_force*(log(glm::length(to) / length)))
                        * to_n - spring_damping * (incident.velocity * to_n - vertex.velocity * to_n);
                }

                acceleration += -viscosity_damping*vertex.velocity;
                vertex.velocity += acceleration * static_cast<float>(delta);
            }

            float charge = 0.05f;
            for (auto& [name1, vertex1] : vertices_)
            {
                glm::vec2 acceleration = {0.f, 0.f};
                for (auto& [name2, vertex2] : vertices_)
                {
                    auto to = (vertex2.position - vertex1.position);
                    if (glm::dot(to, to) < eps)
                    {
                        to = glm::circularRand(charge*10.f);
                    }
                    acceleration += -(charge * to / glm::dot(to, to));
                }
                vertex1.velocity += acceleration * static_cast<float>(delta);
                acceleration += -viscosity_damping*vertex1.velocity;

                vertex1.position += vertex1.velocity * static_cast<float>(delta);

                renderer_.DrawTexture(vertex1.object.GetTexture(),
                                      glm::vec3(ToPixels(vertex1.position), 1.1f),
                                      {64.f, 64.f}, 0.f,
                                      glm::vec4(vertex1.object.GetColor(), 1.f));
            }
            //Draw roads
            for (auto& [name, vertex] : vertices_)
            {
                //Update position
                for (const auto& [name, length] : vertex.incedent)
                {
                    const auto& incident = vertices_.at(name);
                    renderer_.DrawLine(ToPixels(vertex.position),
                                       ToPixels(incident.position),
                                       10.f, {0.1f,0.1f,0.13f});
                }
            }
        })));
    }

    void Graphics::AddVertex(std::string name, GraphicsObject& object,
                   glm::vec2 initialPosition)
    {
        vertices_.emplace(
            std::make_pair(name, GraphicsVertex{initialPosition, object, {}}));
    }

    void Graphics::AddRoad(const std::string& from, const std::string& to,
                           double length)
    {
        vertices_.at(from).incedent[to] = length;
        vertices_.at(to).incedent[from] = length;
    }

    ProcessPtr Graphics::VehicleRideRoad(const GraphicsObject& vehicle,
                                   const std::string& from,
                                   const std::string& to,
                                   double time)
    {
        return ToPtr(VehicleRide(vehicle, from, to, time,
                                 vertices_, renderer_, scale_));
    }

    Graphics::VehicleRide::VehicleRide(const GraphicsObject& vehicle,
                                       const std::string& from,
                                       const std::string& to, double time,
                                       const std::unordered_map<std::string,
                                       GraphicsVertex>& map,
                                       Renderer& renderer,
                                       double scale)
        : vehicle_(vehicle), from_(from), to_(to), time_(time),
          map_(map), renderer_(renderer), scale_(scale) {}

    void Graphics::VehicleRide::Update(double delta)
    {
        passed += delta;
        if (passed >= time_)
            Stop();
        float t = passed / time_;

        const auto& from = map_.at(from_).position;
        const auto& to = map_.at(to_).position;

        auto dir = (to - from);
        auto pos = from + dir * t;
        float dot = dir.x;
        float det = - dir.y;
        float angle = atan2(det, dot);
        renderer_.DrawTexture(vehicle_.GetTexture(),
                              glm::vec3(static_cast<float>(scale_) * pos, 1.2f),
                              {32.f, 32.f}, -angle, glm::vec4(vehicle_.GetColor(), 1.f));
    }

    ProcessPtr Graphics::VehicleRideVertex(const GraphicsObject& vehicle,
                                     const std::string& vertex_name)
    {
        return ToPtr(WhileTrue([vertex_name, this, &vehicle](double delta)
        {
            renderer_.DrawTexture(vehicle.GetTexture(),
                                  glm::vec3(ToPixels(vertices_.at(vertex_name).position), 1.2f),
                                  {32.f, 32.f}, 0,
                                  glm::vec4(vehicle.GetColor(), 1.f));
        }));
    }
}
