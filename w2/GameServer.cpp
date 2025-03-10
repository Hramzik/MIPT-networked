#include <iostream>
#include <stdexcept>
#include <cstring>
#include <sstream>

#include "GameServer.h"

int main() {

    GameServer gameServer;
    gameServer.start();
    return 0;
}

GameServer::GameServer():
        server(nullptr),
        nextPlayerId(1)
{
    if (enet_initialize() != 0) throw std::runtime_error("Cannot init ENet.");

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 10888;
    server = enet_host_create(&address, 32, 2, 0, 0);

    if (!server) throw std::runtime_error("Cannot create ENet server.");
}

GameServer::~GameServer() {

    if (server) enet_host_destroy(server);
    enet_deinitialize();
}

void GameServer::sendNewPlayerInfo(const PlayerInfo& newPlayer) {

    for (const auto& [peer, player] : players) {

        if (player.id == newPlayer.id) continue;

        char message[64];
        snprintf(message, sizeof(message), "player %d %s", newPlayer.id, newPlayer.name.c_str());

        // reliable
        ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
    }
}

void GameServer::sendPlayersInfo(ENetPeer* dstPeer) {

    for (const auto& [peer, player] : players) {

        if (peer == dstPeer) continue;

        char message[64];
        snprintf(message, sizeof(message), "player %d %s", player.id, player.name.c_str());

        // reliable
        ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(dstPeer, 0, packet);
    }
}

void GameServer::parseClientMessage(ENetPeer* srcPeer, const std::string& message) {

    if (message.find("pos") == 0) {

        int srcId   = players[srcPeer].id;
        int srcPing = srcPeer->roundTripTime;

        std::istringstream stream(message);
        std::string token;
        stream >> token; // skip "pos"
        float posX, posY;
        stream >> posX >> posY;

        for (const auto& [peer, player] : players) {

            if (peer == srcPeer) continue;

            char posMsg[64];
            snprintf(posMsg, sizeof(posMsg), "pos %d %f %f", srcId, posX, posY);

            // unreliable
            ENetPacket* pos_packet = enet_packet_create(posMsg, strlen(posMsg) + 1, 0);
            enet_peer_send(peer, 0, pos_packet);

            // also send ping
            char pingMsg[64];
            snprintf(pingMsg, sizeof(pingMsg), "ping %d %d", srcId, srcPing);

            // unreliable
            ENetPacket* ping_packet = enet_packet_create(pingMsg, strlen(pingMsg) + 1, 0);
            enet_peer_send(peer, 0, ping_packet);
        }
    }
}

void GameServer::handleEvents() {

    ENetEvent event;
    while (enet_host_service(server, &event, 10) > 0) {

        switch (event.type) {

            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "new connection from " << event.peer->address.host << ":" << event.peer->address.port << "\n";
                players[event.peer] = { nextPlayerId, "Player" + nextPlayerId };
                ++nextPlayerId;
                sendNewPlayerInfo(players[event.peer]);
                sendPlayersInfo(event.peer);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "new message:" << (const char*) event.packet->data << "\n";
                parseClientMessage(event.peer, (const char*) event.packet->data);
                enet_packet_destroy(event.packet);
                break;

            default: break;
        }
    }
}

void GameServer::start() {

    while (true) {

        handleEvents();
    }
}

