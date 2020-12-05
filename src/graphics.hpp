#pragma once
#include "glm/vec2.hpp"
#include "process_manager.hpp"
#include "renderer.hpp"
#include "vertex.hpp"
#include "vehicle.hpp"
#include "roads.hpp"
#include <unordered_set>
#include "graphics_object.hpp"

namespace transport
{
  
    struct GraphicsVertex
    {
        glm::vec2 position;
        GraphicsObject& object;
        std::unordered_map<std::string, double> incedent;
        glm::vec2 velocity {0.f, 0.f};
    };

    /*
    ** Отвечает за рисование вершин, дорог и машин, их позицию
    */
    class Graphics
    {
    public:

        Graphics(Renderer& renderer, ProcessManager& p_manager_);

        void AddVertex(std::string name, GraphicsObject& object,
                       glm::vec2 initialPosition = {0., 0.});
        void AddRoad(const std::string& from, const std::string& to,
                     double length);

        ProcessPtr VehicleRideRoad(const GraphicsObject& vehicle,
                             const std::string& from, const std::string& to,
                             double time);
        ProcessPtr VehicleRideVertex(const GraphicsObject& vehicle,
                               const std::string& vertex_name);
    private:
        ProcessManager& p_manager_;
        Renderer& renderer_;

        double scale_ = 200.;
        template <typename T>
        T ToPixels(const T& vec)
        {
            return vec * static_cast<float>(scale_);
        }
        std::unordered_map<std::string, GraphicsVertex> vertices_;

        class VehicleRide : public Process
        {
        public:
            VehicleRide(const GraphicsObject& vehicle,
                        const std::string& from,
                        const std::string& to, double time,
                        const std::unordered_map<std::string, GraphicsVertex>&,
                        Renderer& renderer, double scale);
            void Update(double delta) override;

            const GraphicsObject& vehicle_;
            std::string from_, to_;
            double time_;
            double passed = 0.;
            double scale_;
            const std::unordered_map<std::string, GraphicsVertex>& map_;
            Renderer& renderer_;

        };
    };
}
