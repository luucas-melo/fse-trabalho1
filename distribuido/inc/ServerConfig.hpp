#pragma once

#include <vector>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <json.hpp>

typedef struct address
{
    std::string ip;
    int port;
} address;

class ServerConfig
{
    using json = nlohmann::json;

public:
    ServerConfig(const char *path);
    std::string getName();
    address getAddress();
    json getTrafficLights();
    json getButtons();

private:
    std::string name_;
    address address_;
    json trafficLights_;
    json buttons_;
};