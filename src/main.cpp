#include <fstream>
#include <semaforos.h>
#include <json.hpp>
#include <iostream>
#include "ServerConfig.hpp"

using namespace std;

int main(int argc, char const *argv[])
{


    ServerConfig config = ServerConfig(argv[1]);

    start_semaforo();

    return 0;
}