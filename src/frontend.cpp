#include "frontend.hpp"

using json = nlohmann::json;
namespace transport
{
    Frontend::Frontend(const json& routes, Graphics& graphics)
        : graphics_(graphics)
    {
        //Build Graph, fill satelite data

        //Initialize Router
        //
        //Initialize Renderer, create verticies, edges, etc...

        //First pass. Add all verticies
        for (auto& [name, vertexJson] : routes.items())
        {
            graphics_.AddVertex(name, vertex_factory_(vertexJson));
            //TODO add for graph
        }

        //Second pass. Add roads
        for (auto& [fromName, vertexJson] : routes.items())
        {
            for (auto& [toName, roadJson] : vertexJson.at("incident").items())
            {
                //TODO add for graph
            }
        }

    }

    std::vector<ProcessPtr> Frontend::GenerateProcesses(const json &vehicles) const
    {
        std::vector<ProcessPtr> result;

        for (const auto& [vehicleName, vehicleJson] : vehicles.items())
        {
            graphics_.AddVertex(vehicleName, vehicle_factory_(vehicleJson));

            //TODO get route
        }
        return result;
    }
}
