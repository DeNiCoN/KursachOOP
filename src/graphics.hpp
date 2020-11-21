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
        std::unordered_set<std::string> incedent;
        GraphicsObject& object;
    };

    /*
    ** Отвечает за рисование вершин, дорог и машин, их позицию
    */
    class Graphics
    {
    private:
        using Renderer = Renderer;
    public:

        Graphics(Renderer& renderer);

        void AddVertex(std::string name, const GraphicsObject& object,
                       glm::vec2 initialPosition = {0., 0.});
        void AddRoad(const std::string& from, const std::string& to);

        void VehicleRideRoad(const std::string& vehicle_name,
                              const std::string& from, const std::string& to);
        void VehicleRideVertex(const std::string& vehicle_name,
                                const std::string& vertex_name);
    private:
        ProcessManager p_manager_;
        Renderer& renderer_;

        std::unordered_map<std::string, GraphicsVertex> vertices_;
    };
}
