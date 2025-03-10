#pragma once

#include <enet/enet.h>
#include <string>

class LobbyServer {
public:
    LobbyServer();
    ~LobbyServer();
    void start();

private:
    void handleEvents();
    void parseClientMessage(const std::string& message);

    static inline std::string GAME_SERVER_ADDR = "localhost:10888";

    ENetHost* server;
    bool gameSessionStarted;
};

