#include <iostream>
#include <fstream>
#include "graph.hpp"
#include "router.hpp"
#include "vertex_type.hpp"
#include "application.hpp"

using namespace std;
using namespace transport;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    ifstream fs("..\\..\\..\\example_jsons\\example1.json");
    json input;
    fs >> input;

    Application app(input.at("vertices"));
    app.LoadVehicles(input.at("vehicles"));

    return app.Start();
}
