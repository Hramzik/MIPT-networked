#include <iostream>
#include <stdexcept>
#include <cstring>

#include "LobbyServer.h"

int main() {

    LobbyServer lobbyServer;
    lobbyServer.start();
    return 0;
}

LobbyServer::LobbyServer():
        server(nullptr),
        gameSessionStarted(false)
{
    if (enet_initialize() != 0) throw std::runtime_error("Cannot init ENet.");

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 10887;
    server = enet_host_create(&address, 32, 2, 0, 0);

    if (!server) throw std::runtime_error("Cannot create ENet server.");
}

LobbyServer::~LobbyServer() {

    if (server) enet_host_destroy(server);
    enet_deinitialize();
}

void LobbyServer::handleEvents() {

    ENetEvent event;

    while (enet_host_service(server, &event, 10) > 0) {

        switch (event.type) {

            case ENET_EVENT_TYPE_CONNECT:
                printf("new connection from %x:%u\n", event.peer->address.host, event.peer->address.port);
                if (gameSessionStarted) {
                    std::string message = "gameserver " + GAME_SERVER_ADDR;
                    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(event.peer, 0, packet);
                }
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "new message: " << (const char*)event.packet->data << "\n";
                parseClientMessage((const char*)event.packet->data);
                enet_packet_destroy(event.packet);
                break;

            default: break;
        }
    }
}

void LobbyServer::parseClientMessage(const std::string& message) {

    if (message.find("start") == 0) {

        if (gameSessionStarted) return;
        gameSessionStarted = true;

        std::cout << "broadcasting game server addr...\n";

        std::string message = "gameserver " + GAME_SERVER_ADDR;
        ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_host_broadcast(server, 0, packet);
    }
}

void LobbyServer::start() {

    while (true) handleEvents();
}

