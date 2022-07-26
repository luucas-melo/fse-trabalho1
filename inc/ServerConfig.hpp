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


typedef struct address
{
    std::string ip;
    int port;
} address;

class ServerConfig
{
public:
    ServerConfig(const char *path);
};