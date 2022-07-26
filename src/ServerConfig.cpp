#include "ServerConfig.hpp"
#include <json.hpp>
#include <string>

using namespace std;


ServerConfig::ServerConfig(const char *file)
{

    using json = nlohmann::json;

    string directory("configs/");
    string fileName(file);
    string path(directory+=fileName);

    std::cout << path << std::endl;
    std::ifstream f(path);
    json data = json::parse(f);

    std::string s = data.dump();
    std::cout << data["name"] << std::endl;

}