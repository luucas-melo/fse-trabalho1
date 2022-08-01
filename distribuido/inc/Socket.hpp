#pragma once

#include <string>
#include <thread>
#include <streambuf>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

class Socket
{
public:
    static Socket *getInstance();

    void connectSocket(char const *ip, int port);
    void closeConnection();
    int getConnection();
    std::string readMessage();
    void sendMessage(std::string message);

protected:
    int socket_ = -1;
    const char *ip_;
    int port_;

private:
    static Socket *inst_;
    Socket();
    Socket(const Socket &);
    Socket &operator=(const Socket &);
};
