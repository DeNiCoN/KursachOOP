#include <iostream>
#include "graphics.hpp"
#include "frontend.hpp"

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

