#include <iostream>
#include "graph.hpp"
#include "router.hpp"
#include "vertex_type.hpp"
#include "application.hpp"

using namespace std;
using namespace transport;
using json = nlohmann::json;

int main()
{
    json input;
    transport::Graph graph(6);
    std::vector<VertexType> type;
    for (size_t i = 0; i < 6; i++)
    {
        type.push_back(static_cast<VertexType>(i % 2));
        type.push_back(static_cast<VertexType>(i % 3));
        graph.AddVertex(type);
    }
    graph.AddEdge(0, 1, 20);
    graph.AddEdge(1, 2, 120);
    graph.AddEdge(2, 3, 20);
    graph.AddEdge(1, 4, 50);
    graph.AddEdge(4, 5, 20);
    graph.AddEdge(5, 3, 20);

    transport::RouterBreadthFS router;
    transport::RouterDepthFS router2;
    std::vector<int> rout;
    rout = router.FindRoute(graph, 0, 3);
    for (size_t i = 0; i < rout.size(); i++)
    {
        std::cout << rout[i] << std::endl;
    }
    rout = router2.FindRoute(graph, 0, 3);
    for (size_t i = 0; i < rout.size(); i++)
    {
        std::cout << rout[i] << std::endl;
    }
    std::cout << graph.GetRandVertex() << std::endl;
    std::cout << graph.GetRandVertex(VertexType::RECOLOR) << std::endl;
    std::cout << graph.GetRandVertex(VertexType::POLICE) << std::endl;
    //    cin >> input;

//    Application app(input.at("vertices"));
//    app.LoadVehicles(input.at("vehicles"));

//    return app.Start();
}
