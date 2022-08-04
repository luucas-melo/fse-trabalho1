#include <fstream>
#include <TrafficLight.hpp>
#include <messageHandler.hpp>
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
    TrafficLight trafficLight = TrafficLight(config.getTrafficLights(), config.getButtons());
    MessageHandler messageHandler = MessageHandler(config.getName(), trafficLight);

    try
    {
        socket->connectSocket(config.getAddress().ip.c_str(), config.getAddress().port);
        socket->sendMessage(messageHandler.messageBuilder("connectionId", "1"));
        std::cout << "CONEXÃO ENVIADA" << '\n';
    }
    catch (std::exception &e)
    {
        cerr << e.what() << endl;
        cout << "Terminating..." << endl;
        Socket::getInstance()->closeConnection();
        exit(0);
    }
    std::thread messageThread(&MessageHandler::listen, messageHandler);

    trafficLight.start();

    messageThread.join();

    return 0;
}