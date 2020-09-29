#pragma once
#include "glm/vec2.hpp"
#include "process_manager.hpp"
#include "empty_renderer.hpp"
#include "vechicles.hpp"
#include "vertexes.hpp"
#include "roads.hpp"

namespace Transport
{
    struct GraphicsVertex
    {
        const std::string name;
        VertexPtr vertexPtr;
        glm::vec2 position;
    };

    struct GraphicsRoad
    {
        GraphicsVertex& from;
        GraphicsVertex& to;
        RoadPtr roadPtr;
    };

    struct GraphicsVechicle
    {
        const std::string name;
        VechiclePtr vechiclePtr;
        glm::vec2 position;
    };

    /*
    ** Отвечает за рисование вершин, дорог и машин, их позицию
    */
    class Graphics
    {
    private:
        using Renderer = EmptyRenderer;
    public:

        Graphics(Renderer& renderer);

        void addVertex(std::string name, VertexPtr);
        void addVechicle(std::string name, VechiclePtr);
        void addRoad(const std::string& from, const std::string& to, RoadPtr);

        void vechicleRideRoad(const std::string& vechicleName,
                              const std::string& from, const std::string& to);
        void vechicleRideVertex(const std::string& vechicleName,
                                const std::string& vertexName);

        void update(double delta);
    private:
        ProcessManager m_pManager;
        Renderer& m_renderer;

        //Using string_view for memory efficiency at cost of
        //some cpu time while filling up graph
        std::unordered_map<std::string_view, GraphicsVertex> m_vertexes;
        std::vector<GraphicsRoad> m_roads;
        std::unordered_map<std::string_view, GraphicsVechicle> m_vechicles;

        std::unordered_map<std::string_view,
                           std::unordered_map<std::string_view,
                                              std::reference_wrapper<GraphicsRoad>
                                              >> m_graph;
       
    };
}
