#pragma once

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <atomic>

#include "socket_tools.h"

class Client
{
public:
    Client(const std::string &port);
    ~Client();
    void connect(const std::string &name);
    void run();

private:
    void send_messages();
    void receive_messages();

    int sfd;
    addrinfo server_addr;
    std::atomic<bool> running;
    std::thread send_thread;
    std::thread receive_thread;
};

