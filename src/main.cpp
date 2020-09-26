#include <iostream>
#include <nlohmann/json.hpp>
#include "process_manager.hpp"
#include "frontend.hpp"

using namespace std;
using namespace Transport;
using json = nlohmann::json;

int main()
{
    json input;
    cin >> input;
    Frontend front(input.at("routes"));
    auto processes = front.generateProcesses(input.at("vechicles"));
    ProcessManager pm;
    pm.Add(processes.begin(), processes.end());
    return 0;
}

