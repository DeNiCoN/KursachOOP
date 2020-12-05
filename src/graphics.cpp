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
            for (auto& [name, vertex] : vertices_)
            {
                //Update position
                float spring_damping = 0.001f;
                float spring_force = 10.f;
                float viscosity_damping = 2.f;

                glm::vec2 acceleration = {0.f, 0.f};
                for (const auto& [name, length] : vertex.incedent)
                {
                    const auto& incident = vertices_.at(name);
                    auto to = (incident.position - vertex.position);
                    if (glm::dot(to, to) < 0.00000000001)
                    {
                        to = glm::circularRand(length/0.1f);
                    }
                    auto to_n = glm::normalize(to);
                    acceleration += static_cast<float>(spring_force*(glm::length(to) - length))
                        * to_n - spring_damping * (incident.velocity * to_n - vertex.velocity * to_n);
                }

                acceleration += -viscosity_damping*vertex.velocity;
                vertex.velocity += acceleration * static_cast<float>(delta);
                vertex.position += vertex.velocity * static_cast<float>(delta);
                renderer_.DrawTexture(vertex.object.GetTexture(),
                                      glm::vec3(ToPixels(vertex.position), 0.f),
                                      {128.f, 128.f}, 0.f,
                                      glm::vec4(vertex.object.GetColor(), 1.f));
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
        return ToPtr(MakeConsecutive(
                         Callback([from, to](){std::cout << "vehicle ride from "
                                                         << from << " to " << to << std::endl; }),
                         Wait(time)
                         ));
    }

    ProcessPtr Graphics::VehicleRideVertex(const GraphicsObject& vehicle,
                                     const std::string& vertex_name)
    {
        return make_unique<Endless>();
    }
}
