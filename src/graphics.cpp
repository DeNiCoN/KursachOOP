#include "graphics.hpp"
#include "processes.hpp"

namespace transport
{
    using namespace std;
    using namespace processes;

    Graphics::Graphics(Renderer& renderer)
        : renderer_(renderer)
    {
    }



    ProcessPtr Graphics::VehicleRideRoad(const GraphicsObject& vehicle,
                                   const std::string& from,
                                   const std::string& to,
                                   double time)
    {
        return ToPtr(MakeConsecutive(
                         Callback([from, to](){std::cout << "vehicle ride from "
                                                         << from << " to " << to << std::endl; }),
                         Wait(time)
                         ));
    }

    ProcessPtr Graphics::VehicleRideVertex(const GraphicsObject& vehicle,
                                     const std::string& vertex_name)
    {
        return make_unique<Endless>();
    }
}
