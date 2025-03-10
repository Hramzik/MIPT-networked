#pragma once

#include <enet/enet.h>
#include <raylib.h>
#include <string>
#include <map>

struct PlayerInfo {

    std::string name;
    bool isLoaded;
    Vector2 pos;
    int ping;
};

class Client {
public:
    Client();
    ~Client();
    void start();

private:
    void connectToLobbyServer();
    void connectToGameServer (const std::string& address);
    void handleLobbyEvents();
    void handleGameEvents();
    void sendStartCommand();
    void sendPosition();

    void updatePosition(float dt);
    void draw();

    void parseLobbyMessage(const std::string& message);
    void parseGameMessage     (const std::string& message);
    void parseNewPlayerInfo   (const std::string& message);
    void parsePlayersPosition (const std::string& message);
    void parsePlayersPing     (const std::string& message);

    ENetHost* client;
    ENetPeer* lobbyPeer;
    ENetPeer* gamePeer;
    float posx, posy;
    float velx, vely;
    bool connectedToLobby;
    bool connectedToGame;
    std::map<int, PlayerInfo> players;
    
};

