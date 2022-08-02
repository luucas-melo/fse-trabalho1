#include "Socket.hpp"
#include <TrafficLight.hpp>

class MessageHandler
{
public:
    MessageHandler(std::string hostName, TrafficLight &trafficLight);
    void listen();
    void handleReceivedMessage(const char *message);

    std::string messageBuilder(const char *type, const char *message);
    void sendMessage(const char *message);

private:
    Socket *socket_;
    const char *hostName_;
    TrafficLight *trafficLight_;
};