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
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    ifstream fs(argv[1]);
    json input;
    fs >> input;

    Application app(input.at("vertices"));
    app.LoadVehicles(input.at("vehicles"));

    return app.Start();
}
