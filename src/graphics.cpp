#include "graphics.hpp"

namespace Transport
{
    using namespace std;

    Graphics::Graphics(Renderer& renderer)
        : m_renderer(renderer)
    {
    }


    void Graphics::addVertex(std::string name, VertexPtr ptr)
    {
        GraphicsVertex n {move(name), move(ptr)};
        m_vertexes.insert({n.name, move(n)});
    }
    void Graphics::addVechicle(std::string name, VechiclePtr ptr)
    {
        GraphicsVechicle n {move(name), move(ptr)};
        m_vechicles.insert({n.name, move(n)});
    }

    void Graphics::addRoad(const std::string& from, const std::string& to,
                           RoadPtr ptr)
    {
        m_roads.push_back(GraphicsRoad{m_vertexes.at(from), m_vertexes.at(to), move(ptr)});
        m_graph.at(from).at(to) = m_roads.back();
        m_graph.at(to).at(from) = m_roads.back();
    }

    void Graphics::vechicleRideRoad(const std::string& vechicleName,
                                    const std::string& from, const std::string& to)
    {

    }
    void Graphics::vechicleRideVertex(const std::string& vechicleName,
                                      const std::string& vertexName)
    {

    }

    void Graphics::update(double delta)
    {
        //m_pManager.update(delta);
    }
}
