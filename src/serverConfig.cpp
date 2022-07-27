#include "ServerConfig.hpp"
#include <json.hpp>
#include <string>

using namespace std;

using json = nlohmann::json;

ServerConfig::ServerConfig(const char *file)
{

    string directory("configs/");
    string fileName(file);
    string path(directory += fileName);

    std::cout << path << std::endl;
    std::ifstream f(path);
    json data = json::parse(f);

    std::string s = data.dump();
    std::cout << data["name"] << std::endl;

    name_ = data["name"];
    address_.ip = data["ip_servidor_central"];
    address_.port = data["porta_servidor_central"];
    trafficLights_ = data["trafficLights"];
    // for (json::iterator it = data["trafficLights"].begin(); it != data["trafficLights"].end(); it++)
    // {
    //     std::cout << it.value()["wiringPin"] << '\n';
    // }
}

std::string ServerConfig::getName()
{
    return this->name_;
}

json ServerConfig::getTrafficLights()
{
    return this->trafficLights_;
}

address ServerConfig::getAddress()
{
    return this->address_;
}
