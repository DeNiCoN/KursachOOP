#include "vertices.hpp"
#include "processes.hpp"
#include <glm/gtc/random.hpp>

namespace transport
{
    namespace vertices
    {
        using namespace processes;

        ProcessPtr Basic::VisitDefault(Vehicle& veh)
        {
            return std::make_unique<Wait>(wait_time_);
        }

        ProcessPtr Basic::PassDefault(Vehicle& veh)
        {
            return std::make_unique<Wait>(pass_time_);
        }

        ProcessPtr Recolor::Visit(vehicles::Colorful& veh)
        {
            auto color = glm::ballRand(1.f);
            auto init = veh.GetColor();
            auto to = color - init;
            return ToPtr(InterpolateCallback(recolor_time_, [init, to, &veh](float t)
            {
                veh.SetColor(init + to * t);
            }));
        }
    }
}
