#include <messageHandler.hpp>
#include <sstream>
#include <json.hpp>

using json = nlohmann::json;

MessageHandler::MessageHandler(std::string hostName, TrafficLight &trafficLight)
{

    socket_ = Socket::getInstance();
    hostName_ = hostName.c_str();
    this->trafficLight_ = &trafficLight;
    std::cout << "HOST" << trafficLight.currentState << '\n';
}

void MessageHandler::listen()
{
    std::cout << "Listening for events..." << std::endl;
    while (1)
    {
        std::string data = socket_->readMessage();
        handleReceivedMessage(data.c_str());
    }
}

std::string MessageHandler::messageBuilder(const char *type, const char *message)
{
    json j;
    j["type"] = type;
    j["message"] = message;
    j["host"] = hostName_;
    std::string messageString = j.dump();
    const char *messageChar = messageString.c_str();

    std::cout << "MESSAGE JSON" << messageChar << '\n';
    return messageString;
}

void MessageHandler::handleReceivedMessage(const char *message)
{
    json j = json::parse(message);

    if (j["type"] == "nightMode")
    {

        trafficLight_->setNightMode(j["message"]);

        std::cout << "NIGHT MODE" << message << '\n';
    }

    std::cout << "RECEIVED MESSAGE" << message << '\n';
}