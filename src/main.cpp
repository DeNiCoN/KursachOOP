#include <iostream>
#include <nlohmann/json.hpp>
#include "frontend.hpp"

using namespace std;
using namespace Transport;
using json = nlohmann::json;

int main()
{
    json input;
    cin >> input;
    Frontend front(input.at("routes"));
    return 0;
}

