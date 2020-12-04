#include "application.hpp"
#include <chrono>
#include "texture_loader.hpp"
#include "processes.hpp"

namespace transport
{
    Application::Application(const nlohmann::json& vertices)
        : graphics_(Renderer::GetInstance()), simulation_(graphics_, p_manager_)

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
                double length = 1.;
                if (vertex_json.count("length"))
                    length = vertex_json.at("length");
                simulation_.AddRoad(from_name, to_name, length);
            }
        }
    }

    void Application::LoadVehicles(const nlohmann::json &vehicles)
    {
        for (auto& [name, vehicle_json] : vehicles.items())
        {
            auto vehicle_ptr = vehicle_factory_(vehicle_json);
            vehicle_ptr->SetName(name);

            simulation_.AddVehicle(std::move(vehicle_ptr),
                                   vehicle_json.at("initial"));
        }
    }

    //Fixed timestep game loop
    int Application::Start()
    {
        Renderer& renderer = Renderer::GetInstance();
        bool initialized = renderer.Initialize();

        if (!initialized)
        {
            std::cerr << "Render is not initialized" << std::endl;
            return 1;
        }

        using clock = std::chrono::high_resolution_clock;
        using namespace std::chrono_literals;

        constexpr std::chrono::nanoseconds timestep(16ms);
        constexpr double timestep_as_double =
            timestep.count() / static_cast<double>(std::chrono::nanoseconds(1s).count());

        std::chrono::nanoseconds lag(0ns);
        auto base_time = clock::now();

        /*{
            using namespace processes;
            p_manager_.Add(ToPtr(
                               MakeConsecutive(
                                   Callback([]{std::cout << "Start" << std::endl;}),
                                   Callback([]{std::cout << "Pee pee poo poo check" << std::endl;}),
                                   Wait(4.0),
                                   Callback([]{std::cout << "Wait 4.0 passed" << std::endl;}),
                                   MakeAnd(
                                       MakeConsecutive(
                                           Callback([]{std::cout << "Checking And" << std::endl;}),
                                           Endless()
                                           ),
                                       Wait(5.0),
                                       Wait(1000000.0)
                                       ),
                                   Callback([]{std::cout << "5 sec should have passed" << std::endl;}),
                                   Callback([]{std::cout << "Stopping" << std::endl;})
                                   )
                               ));

            //p_manager_.Add(ToPtr(MakeConsecutive(Wait(1.0))));
        }*/

        while(!renderer.ShouldClose()) {

            auto current_time = clock::now();
            auto frame_time = current_time - base_time;
            base_time = current_time;
            lag += std::chrono::duration_cast<std::chrono::nanoseconds>(frame_time);

            //Update
            while(lag >= timestep) {
                lag -= timestep;

                p_manager_.Update(timestep_as_double);
            }

            //Render
            renderer.DrawTexture(TextureLoader::Load("textures/test.png"), {0., 0., 0.}, {128., 128.}, 0., {1., 0., 1., 1.});
            renderer.Render();
        }

        renderer.Terminate();
        return 0;
    }
}
