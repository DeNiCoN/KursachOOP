#include <iostream>
#include "graphics.hpp"
#include "frontend.hpp"
#include "vertices.hpp"
#include "graph.hpp"
#include "router.hpp"

using namespace std;
using namespace Transport;
using json = nlohmann::json;

EmptyRenderer renderer;
Graphics graphics{renderer};

int main()
{
    json input;
/*                      Test Algo
    std::vector<std::vector<int>> AdjeVert = { {1,4},{0,2},{1,3},{2,5},{0,5},{4,0} };
    std::vector<std::vector<int>> EdgeWeight = { {20,50},{20,20},{20,20},{20,50},{50,50},{50,50} };
    std::vector<int> rout;
    RouterTypeFirst router1;
    rout = router1.FindRoute(AdjeVert, EdgeWeight, 0, 3);
    for (size_t i = 0; i < rout.size(); i++)
    {
        cout << rout[i] << " ";
    }
    std::cout << std::endl;
    RouterTypeSecond router2;
    rout = router2.FindRoute(AdjeVert, EdgeWeight, 0, 3);
    for (size_t i = 0; i < rout.size(); i++)
    {
        cout << rout[i] << " ";
    }*/
    cin >> input;
    Frontend front(input.at("routes"), graphics);
    front.generateProcesses(input.at("vechicles"));
    return 0;
}
