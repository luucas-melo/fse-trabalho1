#include "Socket.hpp"

class MessageHandler
{
public:
    MessageHandler(std::string hostName);
    void listen();
    void handleMessage(const char *message);

    std::string messageBuilder(const char *type, const char *message);
    void sendMessage(const char *message);

private:
    Socket *socket_;
    const char *hostName_;
};