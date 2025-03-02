#include "server.h"
#include "socket_tools.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <cstdlib>
#include <ctime>

int main()
{
    Server server("2025");
    server.run();
    return 0;
}

Server::Server(const std::string &port)
{
    sfd = create_dgram_socket(nullptr, port.c_str(), nullptr);
    if (sfd == -1) throw std::runtime_error("failed to create server socket");
    std::srand(std::time(nullptr));
    std::cout << "server is listening on port " << port << "\n";
}

void Server::broadcast_message(const std::string &message)
{
    for (const auto &client : clients)
    {
        sendto(sfd, message.c_str(), message.size(), 0, (sockaddr *)&client.addr, sizeof(sockaddr_in));
    }
}

void Server::broadcast_message_exept(const std::string &message, sockaddr_in exclude_addr)
{
    for (const auto &client : clients)
    {
        if (client.addr == exclude_addr) continue;
        sendto(sfd, message.c_str(), message.size(), 0, (sockaddr *)&client.addr, sizeof(sockaddr_in));
    }
}

void Server::send_message(const std::string &message, const sockaddr_in &addr)
{
    sendto(sfd, message.c_str(), message.size(), 0, (sockaddr *)&addr, sizeof(sockaddr_in));
}

void Server::handle_message(const std::string &message, const sockaddr_in &client_addr)
{
    std::cout << "new message: " << message << "\n";

    if (message.find("/connect ") == 0)
    {
        clients.push_back({client_addr, message.substr(9)});
        std::cout << "new client connected: " << message.substr(9) << "\n";
        return;
    }

    if (message.find("/c ") == 0)
    {
        broadcast_message(find_client_name(client_addr) + " said: " + message.substr(3));
        return;
    }

    if (message == "/dice")
    {
        send_message("you rolled " + std::to_string(std::rand() % 100), client_addr);
        return;
    }

    if (message == "/help")
    {
        send_message("/c, /mathduel, /dice, /help", client_addr);
        return;
    }

    if (message == "/mathduel")
    {
        if (duel_info.members_count == 0)
        {
            duel_info.first_member = client_addr;
            ++duel_info.members_count;
            broadcast_message_exept("someone is searching for a mathduel! /mathduel to join", client_addr);
            send_message("waiting for another player to join the duel...", client_addr);
        }
        else if (duel_info.members_count == 1)
        {
            if (duel_info.first_member == client_addr) send_message("playing by yourself is kinda sad :/", client_addr);
            duel_info.second_member = client_addr;
            ++duel_info.members_count;
            start_duel();
        }
        else if (duel_info.members_count == 2)
        {
            send_message("please wait for an active duel to finish", client_addr);
        }
        return;
    }

    if (message.find("/ans ") == 0)
    {
        if (duel_info.first_member != client_addr && duel_info.second_member != client_addr)
        {
            send_message("stop griefing!", client_addr);
            return;
        }

        sockaddr_in opponent = (duel_info.first_member == client_addr) ? duel_info.second_member : duel_info.first_member;
        int answer = std::stoi(message.substr(5));
        if (answer == duel_info.problem.answer)
        {
            end_duel();

            if (duel_info.first_member == duel_info.second_member) send_message("you won the duel with yourself!", client_addr);
            else {
                send_message("you won the duel!",    client_addr);
                send_message("you lost the duel, L", opponent);
            }

            broadcast_message("a math duel has ended. the winner is: " + find_client_name(client_addr));
        }
        else
        {
            send_message("wrong answer! think again bozo", client_addr);
        }
        return;
    }
}

void Server::start_duel()
{
    duel_info.problem = generate_math_problem();
    send_message("math duel has started! solve: " + duel_info.problem.task + ", /ans <n> to answer", duel_info.first_member);
    if (duel_info.first_member == duel_info.second_member) return;
    send_message("math duel has started! solve: " + duel_info.problem.task + ", /ans <n> to answer", duel_info.second_member);
}

void Server::end_duel()
{
    duel_info.members_count = 0;
}

MathProblem Server::generate_math_problem()
{
    int a = std::rand() % 10;
    int b = std::rand() % 10;
    int op = std::rand() % 3; // 0: +, 1: -, 2: *
    std::string task;
    int answer;

    switch (op)
    {
    case 0:
        task = std::to_string(a) + " + " + std::to_string(b);
        answer = a + b;
        break;
    case 1:
        task = std::to_string(a) + " - " + std::to_string(b);
        answer = a - b;
        break;
    case 2:
        task = std::to_string(a) + " * " + std::to_string(b);
        answer = a * b;
        break;
    }

    return {task, answer};
}

std::string Server::find_client_name(sockaddr_in addr)
{
    for (auto i : clients)
    {
        if (i.addr != addr) continue;
        return i.name;
    }

    return "client not found";
}

void Server::run()
{
    while (true)
    {
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(sfd, &readSet);

        timeval timeout = {0, 100000}; // 100 ms
        select(sfd + 1, &readSet, nullptr, nullptr, &timeout);

        if (FD_ISSET(sfd, &readSet))
        {
            constexpr size_t buf_size = 1000;
            char buffer[buf_size];
            memset(buffer, 0, buf_size);

            sockaddr_in client_addr;
            socklen_t addr_len = sizeof(sockaddr_in);
            ssize_t numBytes = recvfrom(sfd, buffer, buf_size - 1, 0, (sockaddr *)&client_addr, &addr_len);

            if (numBytes > 0)
            {
                buffer[numBytes] = '\0';
                handle_message(buffer, client_addr);
            }
        }
    }
}

bool operator== (sockaddr_in a, sockaddr_in b)
{
    if (a.sin_addr != b.sin_addr) return false;
    if (a.sin_port != b.sin_port) return false;
    return true;
}

bool operator!= (sockaddr_in a, sockaddr_in b)
{
    return !(a==b);
}

bool operator== (in_addr a, in_addr b)
{
    if (a.s_addr != b.s_addr) return false;
    return true;
}

bool operator!= (in_addr a, in_addr b)
{
    return !(a==b);
}
