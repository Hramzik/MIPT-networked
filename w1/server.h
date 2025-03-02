#pragma once

#include <vector>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unordered_map>

bool operator== (sockaddr_in a, sockaddr_in b);
bool operator!= (sockaddr_in a, sockaddr_in b);
bool operator== (in_addr a, in_addr b);
bool operator!= (in_addr a, in_addr b);

struct ClientInfo
{
    sockaddr_in addr;
    std::string name;
};

struct MathProblem
{
    std::string task;
    int answer;
};

struct DuelInfo
{
    int members_count;
    sockaddr_in first_member;
    sockaddr_in second_member;
    MathProblem problem;
};

class Server
{
public:
    Server(const std::string &port);
    void run();

private:
    int sfd;
    std::vector<ClientInfo> clients;
    DuelInfo duel_info = {0, 0, 0, {}};

    void broadcast_message(const std::string &message);
    void broadcast_message_exept(const std::string &message,  sockaddr_in exclude_addr);
    void send_message(const std::string &message, const sockaddr_in &addr);
    void handle_message(const std::string &message, const sockaddr_in &client_addr);
    void start_duel();
    void end_duel  ();
    MathProblem generate_math_problem();
    std::string find_client_name(sockaddr_in addr);
};

