#include <iostream>
#include <nlohmann/json.hpp>
#include "process_manager.hpp"
#include "frontend.hpp"
#include "vertexes.hpp"
#include "graph.hpp"

using namespace std;
using namespace Transport;
using json = nlohmann::json;

EmptyRenderer renderer;
Graphics graphics{renderer};

int main()
{
    json input;
    cin >> input;
    Frontend front(input.at("routes"), graphics);
    front.generateProcesses(input.at("vechicles"));
    return 0;
}
