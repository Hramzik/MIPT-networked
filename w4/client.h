#pragma once
#include <enet/enet.h>
#include <vector>
#include "entity.h"
#include "protocol.h"
#include "raylib.h"

class Client {
public:
    Client();
    ~Client();
    void run();

private:

    void initPeers();
    void initScreen();
    void handleEvents();
    void moveMyEntity();
    void draw();

    void onNewEntityPacket(ENetPacket *packet);
    void onSetControlledEntity(ENetPacket *packet);
    void onSnapshot(ENetPacket *packet);

    ENetHost *client;
    ENetPeer *serverPeer;
    std::vector<Entity> entities;
    uint16_t my_entity;
    bool connected;

    Camera2D camera = { {0, 0}, {0, 0}, 0.f, 1.f };

private:
    static const float inline MyEntitySpeed = 100.f;
};

