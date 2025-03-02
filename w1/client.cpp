#include "client.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

int main()
{
    std::cout << "/connect <name> to connect to server\n";
    Client client("2025");
    client.run();
    return 0;
}

Client::Client(const std::string &port)
{
    sfd = create_dgram_socket("localhost", port.c_str(), &server_addr);
    if (sfd == -1) throw std::runtime_error("Failed to create client socket");
    running = true;
}

Client::~Client()
{
    running = false;
    if (send_thread.joinable()) send_thread.join();
    if (receive_thread.joinable()) receive_thread.join();
    close(sfd);
}

void Client::connect(const std::string &name)
{
    sendto(sfd, ("/connect " + name).c_str(), name.size() + 9, 0, server_addr.ai_addr, server_addr.ai_addrlen);
}

void Client::send_messages()
{
    while (running)
    {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "/exit")
        {
            running = false;
            break;
        }
        sendto(sfd, input.c_str(), input.size(), 0, server_addr.ai_addr, server_addr.ai_addrlen);
    }
}

void Client::receive_messages()
{
    char buffer[1024];
    while (running)
    {
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(sfd, &readSet);

        timeval timeout = {1, 0};
        if (select(sfd + 1, &readSet, nullptr, nullptr, &timeout) > 0)
        {
            if (FD_ISSET(sfd, &readSet))
            {
                memset(buffer, 0, sizeof(buffer));
                ssize_t numBytes = recvfrom(sfd, buffer, sizeof(buffer) - 1, 0, nullptr, nullptr);
                if (numBytes > 0)
                {
                    std::cout << "\nServer: " << buffer << "\n";
                    std::cout << "> " << std::flush;
                }
            }
        }
    }
}

void Client::run()
{
    send_thread = std::thread(&Client::send_messages, this);
    receive_thread = std::thread(&Client::receive_messages, this);

    send_thread.join();
    receive_thread.join();
}