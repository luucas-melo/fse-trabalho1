#include <fstream>
#include <TrafficLight.hpp>
#include <json.hpp>
#include <iostream>
#include "ServerConfig.hpp"

using namespace std;

int main(int argc, char const *argv[])
{

    ServerConfig config = ServerConfig(argv[1]);

    TrafficLight trafficLight = TrafficLight(config.getTrafficLights());

    return 0;
}