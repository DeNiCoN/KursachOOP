#include "simulation.hpp"

namespace transport
{
    Simulation::Simulation(Graphics& graphics, ProcessManager& p_manager)
        : graphics_(graphics), p_manager_(p_manager)
    {
    }
}
