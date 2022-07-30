#include <fstream>
#include <TrafficLight.hpp>
#include <json.hpp>
#include <iostream>
#include "ServerConfig.hpp"
#include <thread>
#include <wiringPi.h>
#include <Socket.hpp>
#include <exception>
using namespace std;

using json = nlohmann::json;

int main(int argc, char const *argv[])
{

    ServerConfig config = ServerConfig(argv[1]);
    Socket *socket = Socket::getInstance();

    try
    {
        socket->connectSocket(config.getAddress().ip.c_str(), config.getAddress().port);
        socket->sendMessage("connectionId");
        std::cout << "MENSAGEM ENVIADA" << '\n';
        usleep(500000);
    }
    catch (std::exception &e)
    {
        cerr << e.what() << endl;
        cout << "Terminating..." << endl;
        Socket::getInstance()->closeConnection();
        exit(0);
    }
    TrafficLight trafficLight = TrafficLight(config.getTrafficLights(), config.getButtons());

    trafficLight.start();

    return 0;
}