#include <iostream>
#include "application.hpp"

using namespace std;
using namespace transport;
using json = nlohmann::json;

int main()
{
    json input;
    cin >> input;

    Application app(input.at("vertices"));
    app.LoadVehicles(input.at("vehicles"));

    app.Start();
    return 0;
}
