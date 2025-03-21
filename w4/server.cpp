#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "server.h"

int main(int argc, const char **argv) {

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Server server;
    server.run();
    return 0;
}

uint16_t create_random_entity(std::vector<Entity>& entities) {

    uint16_t newEid = entities.size();
    
    static const uint32_t colors[] = {
        0x000000ff,
        0x0000ffff,
        0x00ff00ff,
        0x00ffffff,
        0xff0000ff,
        0xff00ffff,
        0xffff00ff,
        0xffffffff 
    };

    uint32_t color = colors[rand() % 8];

    float x = (rand() % 40 - 20) * 15.f;
    float y = (rand() % 40 - 20) * 15.f;
    float size = 10.f + (rand() % 10);
    Entity ent = {color, x, y, newEid, false, 0.f, 0.f, size};
    entities.push_back(ent);

    return newEid;
}

Server::Server() {

    if (enet_initialize() != 0) { printf("Cannot init ENet"); exit(1); }

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 10131;

    server = enet_host_create(&address, 32, 2, 0, 0);
    if (!server) { printf("Cannot create ENet server\n"); exit(1); }

    constexpr int numAi = 10;
    for (int i = 0; i < numAi; ++i) {

        uint16_t eid = create_random_entity(entities);
        entities[eid].serverControlled = true;
        controlledMap[eid] = nullptr;
    }

    lastTime = enet_time_get();
}

Server::~Server() {

    enet_host_destroy(server);
    atexit(enet_deinitialize);
}

void Server::run() {

    while (true) {
        uint32_t curTime = enet_time_get();
        float dt = (curTime - lastTime) * 0.001f;
        lastTime = curTime;

        handleEvents();
        updateEntities(dt);
        sendSnapshots();
    }
}

void Server::handleEvents() {

    ENetEvent event;
    while (enet_host_service(server, &event, 0) > 0) {

        switch (event.type) {

            case ENET_EVENT_TYPE_CONNECT:
                printf("Connection with %x:%u established\n", event.peer->address.host, event.peer->address.port);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                switch (get_packet_type(event.packet)) {

                    case E_CLIENT_TO_SERVER_JOIN: onJoin(event.packet, event.peer); break;
                    case E_CLIENT_TO_SERVER_STATE: onState(event.packet); break;
                };
                enet_packet_destroy(event.packet);
                break;

            default: break;
        };
    }
}

void Server::onJoin(ENetPacket *packet, ENetPeer *peer) {

    for (const Entity &ent : entities) send_new_entity(peer, ent);

    uint16_t newEid = create_random_entity(entities);
    Entity& ent = entities[newEid];
    // за маленьких играть неинтересно
    if (ent.size < 30) ent.size = 30;
    controlledMap[newEid] = peer;

    for (size_t i = 0; i < server->peerCount; ++i) send_new_entity(&server->peers[i], ent);
    send_set_controlled_entity(peer, newEid);
}

void Server::onState(ENetPacket *packet) {

    uint16_t eid = invalid_entity;
    float x = 0.f, y = 0.f, size = 0.f;
    deserialize_entity_state(packet, eid, x, y, size);

    for (Entity &e : entities) {

        if (e.eid != eid) continue;
        e.x = x;
        e.y = y;
        e.size = size;
    }
}

void Server::updateEntities(float dt) {

    updateBots(dt);
    resolveCollisions();
}

void Server::updateBots(float dt) {

    for (Entity &e : entities) {
        if (!e.serverControlled) continue;
        const float diffX = e.targetX - e.x;
        const float diffY = e.targetY - e.y;
        const float dirX = diffX > 0.f ? 1.f : -1.f;
        const float dirY = diffY > 0.f ? 1.f : -1.f;
        constexpr float spd = 50.f;
        e.x += dirX * spd * dt;
        e.y += dirY * spd * dt;

        if (fabsf(diffX) > 10.f || fabsf(diffY) > 10.f) continue;
        e.targetX = (rand() % 40 - 20) * 15.f;
        e.targetY = (rand() % 40 - 20) * 15.f;
    }
}

void Server::resolveCollisions() {

    for (size_t i = 0; i < entities.size(); ++i) {
    for (size_t j = i + 1; j < entities.size(); ++j) {

        Entity& e1 = entities[i];
        Entity& e2 = entities[j];
        float dx = e1.x - e2.x;
        float dy = e1.y - e2.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance > (e1.size + e2.size) * 0.5f) continue;
        Entity& big   = (e1.size > e2.size) ? e1 : e2;
        Entity& small = (e1.size > e2.size) ? e2 : e1;

        if (small.size >= 10 && big.size < 50) { big.size += small.size * 0.5f; small.size *= 0.5f; }
        small.x = (rand() % 40 - 20) * 15.f;
        small.y = (rand() % 40 - 20) * 15.f;

        if (controlledMap.find(big.eid) != controlledMap.end() && controlledMap[big.eid])
            send_snapshot(controlledMap[big.eid], big.eid, big.x, big.y, big.size);

        if (controlledMap.find(small.eid) != controlledMap.end() && controlledMap[small.eid])
            send_snapshot(controlledMap[small.eid], small.eid, small.x, small.y, small.size);
    }}
}

void Server::sendSnapshots() {

    for (const Entity &e : entities) {
        for (size_t i = 0; i < server->peerCount; ++i) {

            ENetPeer *peer = &server->peers[i];
            if (!peer || controlledMap[e.eid] == peer) continue;
            send_snapshot(peer, e.eid, e.x, e.y, e.size);
        }
    }
}

