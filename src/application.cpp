#include "application.hpp"

namespace transport
{
    Application::Application(const nlohmann::json& vertices)
        : graphics_(renderer_), simulation_(graphics_, p_manager_)

    {
        for (auto& [name, vertex_json] : vertices.items())
        {
            auto vertex = vertex_factory_(vertex_json);
            vertex->SetName(name);
            simulation_.AddVertex(move(vertex));
        }

        //Second pass. Add roads
        for (auto& [from_name, vertex_json] : vertices.items())
        {
            for (auto& [to_name, road_json] : vertex_json.at("incident").items())
            {
                simulation_.AddRoad(from_name, to_name);
            }
        }
    }
}
