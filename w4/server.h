#pragma once
#include <enet/enet.h>
#include <vector>
#include <map>
#include <cmath>
#include "entity.h"
#include "protocol.h"

class Server {
public:
    Server();
    ~Server();
    void run();

private:
    void handleEvents();

    void onJoin(ENetPacket *packet, ENetPeer *peer);
    void onState(ENetPacket *packet);
    void sendSnapshots();

    void updateEntities(float dt);
    void updateBots(float dt);
    void resolveCollisions();

    ENetHost *server;
    std::vector<Entity> entities;
    std::map<uint16_t, ENetPeer*> controlledMap;
    uint32_t lastTime;
};

