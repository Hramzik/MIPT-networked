#include <iostream>
#include <stdexcept>
#include <cstring>
#include <sstream>

#include "Client.h"

int main() {

    Client client;
    client.start();
    return 0;
}

Client::Client():
        client(nullptr),
        lobbyPeer(nullptr),
        gamePeer(nullptr),
        posx(GetRandomValue(100, 700)),
        posy(GetRandomValue(100, 500)),
        velx(0),
        vely(0),
        connectedToLobby(false),
        connectedToGame(false)
{
    if (enet_initialize() != 0) throw std::runtime_error("Cannot init ENet");

    client = enet_host_create(nullptr, 2, 2, 0, 0);

    if (!client) throw std::runtime_error("Cannot create ENet client");
}

Client::~Client() {

    if (client) enet_host_destroy(client);
    enet_deinitialize();
}

void Client::connectToLobbyServer() {

    ENetAddress address;
    enet_address_set_host(&address, "localhost");
    address.port = 10887;
    lobbyPeer = enet_host_connect(client, &address, 2, 0);

    if (!lobbyPeer) throw std::runtime_error("сannot connect to lobby");
}

void Client::connectToGameServer(const std::string& address) {

    int colonPos = address.find(':');
    if (colonPos == std::string::npos) throw std::runtime_error("Invalid address format. Expected 'host:port'.");

    std::string host = address.substr(0, colonPos);
    std::string portStr = address.substr(colonPos + 1);
    int port = std::stoi(portStr);

    ENetAddress gameAddress;
    if (enet_address_set_host(&gameAddress, host.c_str()) != 0) throw std::runtime_error("Failed to resolve host: " + host);
    gameAddress.port = port;
    gamePeer = enet_host_connect(client, &gameAddress, 2, 0);

    if (!gamePeer) throw std::runtime_error("Cannot connect to game server.");
    connectedToGame = true;
}

void Client::sendStartCommand() {

    const char* msg = "start";
    ENetPacket* packet = enet_packet_create(msg, strlen(msg) + 1, ENET_PACKET_FLAG_RELIABLE);

    enet_peer_send(lobbyPeer, 0, packet);
}

void Client::sendPosition() {

    char posMsg[64];
    snprintf(posMsg, sizeof(posMsg), "pos %f %f", posx, posy);
    ENetPacket* packet = enet_packet_create(posMsg, strlen(posMsg) + 1, 0); // Ненадёжная отправка

    enet_peer_send(gamePeer, 0, packet);
}

void Client::updatePosition(float dt) {

    bool left  = IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_RIGHT);
    bool up    = IsKeyDown(KEY_UP);
    bool down  = IsKeyDown(KEY_DOWN);
    constexpr float accel = 30.f;
    velx += ((left ? -1.f : 0.f) + (right ? 1.f : 0.f)) * dt * accel;
    vely += ((up ? -1.f : 0.f) + (down ? 1.f : 0.f)) * dt * accel;
    posx += velx * dt;
    posy += vely * dt;
    velx *= 0.99f;
    vely *= 0.99f;
}

void Client::parseNewPlayerInfo(const std::string& data) {

    std::istringstream stream(data);
    std::string token;
    stream >> token; // skip "player"

    while (stream >> token) {

        int id = std::stoi(token);
        stream >> token;
        std::string name = token;

        players[id] = { name, false, 0 };
    }
}

// изначально задумывалось передавать все позиции в одном пакете
// но потом решил разделить на разные пакеты
void Client::parsePlayersPosition(const std::string& data) {

    std::istringstream stream(data);
    std::string token;
    stream >> token; // skip "pos"
    int id;
    float x, y;

    while (stream >> id >> x >> y) {

        players[id].isLoaded = true;
        players[id].pos = Vector2{x, y};
    }
}

void Client::parsePlayersPing(const std::string& data) {

    std::istringstream stream(data);
    std::string token;
    stream >> token; // skip "ping"
    int id;
    int ping;

    while (stream >> id >> ping) {

        players[id].ping = ping;
    }
}

void Client::draw() {

    BeginDrawing();
    ClearBackground(BLACK);

    DrawText(TextFormat("Connected to lobby: %s", connectedToLobby ? "true" : "false"), 20, 20, 20, WHITE);
    DrawText(TextFormat("Connected to game: %s",  connectedToGame  ? "true" : "false"), 20, 50, 20, WHITE);

    int yOffset = 80;
    for (const auto& [id, player] : players) {

        DrawText(TextFormat("Player %d: %s (Ping: %d)", id, player.name.c_str(), player.ping), 20, yOffset, 20, WHITE);
        yOffset += 25;
    }

    for (const auto& [id, player] : players) {

        if (!player.isLoaded) continue;
        DrawCircleV(player.pos, 10.f, WHITE);
    }

    DrawCircleV(Vector2{posx, posy}, 10.f, RED);

    EndDrawing();
}

void Client::handleLobbyEvents() {

    ENetEvent event;

    while (enet_host_service(client, &event, 10) > 0) {
        switch (event.type) {

            case ENET_EVENT_TYPE_CONNECT:
                connectedToLobby = true;
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "new message: " << (const char*)event.packet->data << "\n";
                parseLobbyMessage((const char*)event.packet->data);
                enet_packet_destroy(event.packet);
                break;

            default: break;
        }
    }
}

void Client::parseLobbyMessage(const std::string& message) {

    if (message.find("gameserver") == 0) {

        std::istringstream stream(message);
        std::string token;
        stream >> token; // skip "gameserver"
        stream >> token; // parse ip
        connectToGameServer(token);
    }
}

void Client::handleGameEvents() {

    ENetEvent event;

    while (enet_host_service(client, &event, 10) > 0) {
        switch (event.type) {

            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "new message: " << (const char*)event.packet->data << "\n";
                parseGameMessage((const char*)event.packet->data);
                enet_packet_destroy(event.packet);
                break;

            default: break;
        }
    }
}

void Client::parseGameMessage(const std::string& message) {

    if (message.find("player") == 0) parseNewPlayerInfo(message);
    if (message.find("pos")    == 0) parsePlayersPosition(message);
    if (message.find("ping")   == 0) parsePlayersPing(message);
}

void Client::start() {

    InitWindow(800, 600, "Client");
    SetTargetFPS(60);
    connectToLobbyServer();

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();
        handleLobbyEvents();

        if (connectedToGame) {
            handleGameEvents();
            sendPosition();
            updatePosition(dt);
        }

        if (IsKeyPressed(KEY_ENTER)) {
            std::cout << "sending start command to lobby server...\n";
            sendStartCommand();
        }

        draw();
    }

    CloseWindow();
}

