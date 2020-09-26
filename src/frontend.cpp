#include "frontend.hpp"

using json = nlohmann::json;
namespace Transport
{
    Frontend::Frontend(const json& routes)
    {
        //Build Graph, fill satelite data

        //Initialize Router
        //
        //Initialize Renderer, create verticies, edges, etc...
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
            //for each item in route generate process chain
            //generate process for task end node

            //Get route
            //from edge id get corresponding edge object

            //Example
            //auto vechicleId = m_graphics.newVechicle(*vechiclePtr);
            //vechiclePtr->visitVertex(edgeIdToRoad[id])
            //process.addChild(m_graphics.VechicleVisitRoad(vechicleId, edgeId))
            //result.push_back(move(process))
            //
            //
            //Может быть всё перенести в Graphics? Тип просто вызывать VechicleVisitRoad
            //без дальнейшего сохранения и возвращения списка процессов. Менеджер процессов
            //перенести внутрь Graphics и добавить что-то типо update(delta) или .run();
            //Вроде звучит норм
        }
        return result;
    }
}
