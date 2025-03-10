#pragma once

#include <enet/enet.h>
#include <string>
#include <map>

struct PlayerInfo {

    int id;
    std::string name;
};

class GameServer {
public:
    GameServer();
    ~GameServer();
    void start();

private:
    void handleEvents();
    void sendNewPlayerInfo(const PlayerInfo& newPlayer);
    void sendPlayersInfo(ENetPeer* dstPeer);
    void parseClientMessage(ENetPeer* srcPeer, const std::string& message);

    ENetHost* server;
    std::map<ENetPeer*, PlayerInfo> players;
    int nextPlayerId;
};

