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
    MessageHandler messageHandler = MessageHandler(config.getName());

    try
    {
        socket->connectSocket(config.getAddress().ip.c_str(), config.getAddress().port);
        socket->sendMessage(messageHandler.messageBuilder("connectionId", "CONECTADO"));
        std::cout << "MENSAGEM ENVIADA" << '\n';
        // sleep(500);
    }
    catch (std::exception &e)
    {
        cerr << e.what() << endl;
        cout << "Terminating..." << endl;
        Socket::getInstance()->closeConnection();
        exit(0);
    }
    TrafficLight trafficLight = TrafficLight(config.getTrafficLights(), config.getButtons());
    std::thread messageThread(&MessageHandler::listen, messageHandler);

    trafficLight.start();

    messageThread.join();

    return 0;
}