#include "vertices.hpp"
#include "processes.hpp"

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
    }
}
