#include "frontend.hpp"

using json = nlohmann::json;
namespace Transport
{
    Frontend::Frontend(const json& routes)
    {
        //Build Graph, fill satelite data

        //Initialize Router
       
    }

    std::vector<ProcessPtr> Frontend::generateProcesses(const json &vechicles) const
    {
        std::vector<ProcessPtr> result;

        for (const auto& vechicleNode : vechicles.items())
        {
            const auto& name = vechicleNode.key();
            const auto& vechicleJson = vechicleNode.value();
            auto vechiclePtr = m_vechicleFactory(vechicleJson);

            //For each task pair get route
            //
        }
        return result;
    }
}
