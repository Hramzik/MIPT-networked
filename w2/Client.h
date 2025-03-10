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
    void handleEvents();
    void sendStartCommand();
    void sendPosition();

    void updatePosition(float dt);
    void draw();

    void parseMessage(const std::string& message);
    void parseGameServerAddr  (const std::string& message);
    void parsePlayersInfo     (const std::string& message);
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

