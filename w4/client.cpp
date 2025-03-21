#include <cstdio>
#include "client.h"

int main(int argc, const char **argv) {

    Client client;
    client.run();
    return 0;
}

Client::Client() {

    initPeers();
    initScreen();
}

Client::~Client() {

    CloseWindow();
    enet_host_destroy(client);
    atexit(enet_deinitialize);
}

void Client::run() {

    while (!WindowShouldClose()) {

        handleEvents();
        moveMyEntity();
        draw();
    }
}

void Client::initPeers() {

    if (enet_initialize() != 0) { printf("Cannot init ENet"); exit(1); }

    client = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!client) { printf("Cannot create ENet client\n"); exit(1); }

    ENetAddress address;
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 10131;

    serverPeer = enet_host_connect(client, &address, 2, 0);
    if (!serverPeer) { printf("Cannot connect to server"); exit(1); }

    my_entity = invalid_entity;
    connected = false;
}

void Client::initScreen() {

    int width = 800;
    int height = 600;
    InitWindow(width, height, "w4 networked MIPT");

    const int scrWidth  = GetMonitorWidth(0);
    const int scrHeight = GetMonitorHeight(0);
    if (scrWidth < width || scrHeight < height) {

        width  = std::min(scrWidth, width);
        height = std::min(scrHeight - 150, height);
        SetWindowSize(width, height);
    }

    camera.target = Vector2{ 0.f, 0.f };
    camera.offset = Vector2{ width * 0.5f, height * 0.5f };
    camera.rotation = 0.f;
    camera.zoom = 1.f;

    SetTargetFPS(60);
}

void Client::handleEvents() {

    ENetEvent event;
    while (enet_host_service(client, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("Connection with %x:%u established\n", event.peer->address.host, event.peer->address.port);
                send_join(serverPeer);
                connected = true;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                switch (get_packet_type(event.packet)) {
                    case E_SERVER_TO_CLIENT_NEW_ENTITY:
                        onNewEntityPacket(event.packet);
                        break;
                    case E_SERVER_TO_CLIENT_SET_CONTROLLED_ENTITY:
                        onSetControlledEntity(event.packet);
                        break;
                    case E_SERVER_TO_CLIENT_SNAPSHOT:
                        onSnapshot(event.packet);
                        break;
                };
                break;
            default:
                break;
        };
    }
}

void Client::moveMyEntity() {

    if (my_entity == invalid_entity) return;

    bool left  = IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_RIGHT);
    bool up    = IsKeyDown(KEY_UP);
    bool down  = IsKeyDown(KEY_DOWN);

    float dt = GetFrameTime();
    for (Entity &e : entities) {

        if (e.eid != my_entity) continue;
        e.x += ((left ? -dt : 0.f) + (right ? +dt : 0.f)) * MyEntitySpeed;
        e.y += ((up   ? -dt : 0.f) + (down  ? +dt : 0.f)) * MyEntitySpeed;
        send_entity_state(serverPeer, my_entity, e.x, e.y, e.size);
    }
}

void Client::draw() {

    BeginDrawing();
    ClearBackground(GRAY);

    BeginMode2D(camera);
    for (const Entity &e : entities) {
        const Rectangle rect = {e.x, e.y, e.size, e.size};
        DrawRectangleRec(rect, GetColor(e.color));
    }
    EndMode2D();

    int yOffset = 20;
    for (const Entity &e : entities) {
        if (e.serverControlled) continue;

        DrawText(TextFormat("Player %d score: %.1f", e.eid, e.size), 20, yOffset, 20, WHITE);
        yOffset += 25;
    }

    EndDrawing();
}

void Client::onNewEntityPacket(ENetPacket *packet) {

    Entity newEntity;
    deserialize_new_entity(packet, newEntity);
    printf("Received new entity (EID: %d)\n", newEntity.eid);

    for (const Entity &e : entities)
        if (e.eid == newEntity.eid)
            return;

    entities.push_back(newEntity);
}

void Client::onSetControlledEntity(ENetPacket *packet) {

    deserialize_set_controlled_entity(packet, my_entity);
}

void Client::onSnapshot(ENetPacket *packet) {

    uint16_t eid = invalid_entity;
    float x = 0.f, y = 0.f, size = 0.f;
    deserialize_snapshot(packet, eid, x, y, size);

    for (Entity &e : entities) {

        if (e.eid != eid) continue;
        e.x = x;
        e.y = y;
        e.size = size;
    }
}

