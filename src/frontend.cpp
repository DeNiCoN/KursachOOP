#include "frontend.hpp"

using json = nlohmann::json;
namespace Transport
{
    Frontend::Frontend(const json& routes, Graphics& graphics)
        : m_graphics(graphics)
    {
        //Build Graph, fill satelite data

        //Initialize Router
        //
        //Initialize Renderer, create verticies, edges, etc...

        //First pass. Add all verticies
        for (auto& [name, vertexJson] : routes.items())
        {
            m_graphics.addVertex(name, m_vertexFactory(vertexJson));
            //TODO add for graph
        }

        //Second pass. Add roads
        for (auto& [fromName, vertexJson] : routes.items())
        {
            for (auto& [toName, roadJson] : vertexJson.at("incident").items())
            {
                m_graphics.addRoad(fromName, toName, m_roadFactory(roadJson));
                //TODO add for graph
            }
        }

    }

    std::vector<ProcessPtr> Frontend::generateProcesses(const json &vehicles) const
    {
        std::vector<ProcessPtr> result;

        for (const auto& [vehicleName, vehicleJson] : vehicles.items())
        {
            m_graphics.addVehicle(vehicleName, m_vehicleFactory(vehicleJson));

            //TODO get route
        }
        return result;
    }
}
