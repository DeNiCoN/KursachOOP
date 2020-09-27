#pragma once
#include "glm/vec2.hpp"
#include "process_manager.hpp"
#include "empty_renderer.hpp"
#include "vechicles.hpp"
#include "vertexes.hpp"
#include "roads.hpp"

namespace Transport
{
    /*
    ** Отвечает за рисование вершин, дорог и машин, их позицию
    */
    class Graphics
    {
    private:
        using Renderer = EmptyRenderer;
    public:
        struct Vertex
        {
            glm::vec2 position;
        };

        struct Road
        {
            Vertex from, to;
        };

        Graphics(Renderer& renderer);

        void addVertex(std::string name, ::Transport::VertexPtr);
        void addVechicle(std::string name, ::Transport::VechiclePtr);
        void addRoad(std::string from, std::string to, ::Transport::RoadPtr);

        void update(double delta);
    private:
        ProcessManager m_pManager;
        Renderer& m_renderer;
    };
}
