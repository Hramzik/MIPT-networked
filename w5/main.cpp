// initial skeleton is a clone from https://github.com/jpcy/bgfx-minimal-example
//
#include <functional>
#include "raylib.h"
#include <enet/enet.h>
#include <math.h>

#include <vector>
#include <deque>
#include "entity.h"
#include "stdio.h"
#include "protocol.h"
#include "mathUtils.h"

struct ClientInput {
    float thr, steer;
    uint32_t tick;
};

struct PredictedState {
    float x, y, ori;
    float vx, vy, omega;
    uint32_t tick;
};

static std::unordered_map<uint16_t, std::deque<PredictedState>> predictedStates;
static std::deque<ClientInput> inputHistory;
static uint32_t currentServerTick = 0;

struct Snapshot {
    float x, y, ori;
    uint32_t serverTime;
};

struct EntityState {
    float x, y, ori;
    float vx, vy, omega;
    uint32_t tick;
};

static std::unordered_map<uint16_t, EntityState> serverState;
static std::unordered_map<uint16_t, EntityState> predictedState;

static std::unordered_map<uint16_t, std::vector<Snapshot>> snapshotsHistory;
static const uint32_t INTERPOLATION_DELAY_MS = 200;

static std::vector<Entity> entities;
static std::unordered_map<uint16_t, size_t> indexMap;
static uint16_t my_entity = invalid_entity;

void on_new_entity_packet(ENetPacket *packet)
{
  Entity newEntity;
  deserialize_new_entity(packet, newEntity);
  auto itf = indexMap.find(newEntity.eid);
  if (itf != indexMap.end())
    return; // don't need to do anything, we already have entity
  indexMap[newEntity.eid] = entities.size();
  entities.push_back(newEntity);
}

void on_set_controlled_entity(ENetPacket *packet)
{
  deserialize_set_controlled_entity(packet, my_entity);
}

template<typename Callable>
static void get_entity(uint16_t eid, Callable c)
{
  auto itf = indexMap.find(eid);
  if (itf != indexMap.end())
    c(entities[itf->second]);
}

void on_snapshot(ENetPacket *packet) {
    uint16_t eid;
    float x, y, ori, vx, vy, omega;
    uint32_t serverTime, tick;
    deserialize_snapshot(packet, eid, x, y, ori, vx, vy, omega, serverTime, tick);
    currentServerTick = tick;

    if (eid == my_entity) {
        auto &myPredictedStates = predictedStates[eid];
        while (!myPredictedStates.empty() && myPredictedStates.front().tick < tick) {
            myPredictedStates.pop_front();
        }
        while (!inputHistory.empty() && inputHistory.front().tick <= tick) {
            inputHistory.pop_front();
        }

        if (!myPredictedStates.empty() && myPredictedStates.front().tick == tick) {
            float dx = x - myPredictedStates.front().x;
            float dy = y - myPredictedStates.front().y;
            float dori = ori - myPredictedStates.front().ori;

            Entity &e = entities[indexMap[eid]];
            e.x += dx;
            e.y += dy;
            e.ori += dori;
            e.vx = vx;
            e.vy = vy;
            e.omega = omega;

            for (auto &state : myPredictedStates) {
                state.x += dx;
                state.y += dy;
                state.ori += dori;
            }

            for (const auto &input : inputHistory) {
                e.thr = input.thr;
                e.steer = input.steer;
                simulate_entity(e, FIXED_DT);
            }
        }
    }

    serverState[eid] = {x, y, ori, vx, vy, omega, tick};
}

static void on_time(ENetPacket *packet, ENetPeer* peer) {
    uint32_t timeMsec, currentTick;
    deserialize_time_msec(packet, timeMsec, currentTick);
    enet_time_set(timeMsec + peer->lastRoundTripTime / 2);
}

static void client_side_prediction(float dt) {
    if (my_entity == invalid_entity) return;

    bool left = IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_RIGHT);
    bool up = IsKeyDown(KEY_UP);
    bool down = IsKeyDown(KEY_DOWN);

    float thr = (up ? 1.f : 0.f) + (down ? -1.f : 0.f);
    float steer = (left ? -1.f : 0.f) + (right ? 1.f : 0.f);

    inputHistory.push_back({thr, steer, currentServerTick});

    Entity &e = entities[indexMap[my_entity]];
    e.thr = thr;
    e.steer = steer;
    simulate_entity(e, dt);

    predictedStates[my_entity].push_back({e.x, e.y, e.ori, e.vx, e.vy, e.omega, currentServerTick});
}

static void draw_entity(const Entity &e) {
    auto serverIt = serverState.find(e.eid);
    if (serverIt == serverState.end()) {
        const float shipLen = 3.f;
        const float shipWidth = 2.f;
        const Vector2 fwd = Vector2{cosf(e.ori), sinf(e.ori)};
        const Vector2 left = Vector2{-fwd.y, fwd.x};
        DrawTriangle(Vector2{e.x + fwd.x * shipLen * 0.5f, e.y + fwd.y * shipLen * 0.5f},
                    Vector2{e.x - fwd.x * shipLen * 0.5f - left.x * shipWidth * 0.5f, e.y - fwd.y * shipLen * 0.5f - left.y * shipWidth * 0.5f},
                    Vector2{e.x - fwd.x * shipLen * 0.5f + left.x * shipWidth * 0.5f, e.y - fwd.y * shipLen * 0.5f + left.y * shipWidth * 0.5f},
                    GetColor(e.color));
        return;
    }

    const auto &server = serverIt->second;
    const auto &predicted = predictedState[e.eid];

    float t = 0.5f;
    float interpX = lerp(server.x, predicted.x, t);
    float interpY = lerp(server.y, predicted.y, t);
    float interpOri = lerp(server.ori, predicted.ori, t);

    const float shipLen = 3.f;
    const float shipWidth = 2.f;
    const Vector2 fwd = Vector2{cosf(interpOri), sinf(interpOri)};
    const Vector2 left = Vector2{-fwd.y, fwd.x};
    DrawTriangle(
        Vector2{interpX + fwd.x * shipLen * 0.5f, interpY + fwd.y * shipLen * 0.5f},
        Vector2{interpX - fwd.x * shipLen * 0.5f - left.x * shipWidth * 0.5f, interpY - fwd.y * shipLen * 0.5f - left.y * shipWidth * 0.5f},
        Vector2{interpX - fwd.x * shipLen * 0.5f + left.x * shipWidth * 0.5f, interpY - fwd.y * shipLen * 0.5f + left.y * shipWidth * 0.5f},
        GetColor(e.color)
    );
}

static void update_net(ENetHost* client, ENetPeer* serverPeer)
{
  ENetEvent event;
  while (enet_host_service(client, &event, 0) > 0)
  {
    switch (event.type)
    {
    case ENET_EVENT_TYPE_CONNECT:
      printf("Connection with %x:%u established\n", event.peer->address.host, event.peer->address.port);
      send_join(serverPeer);
      break;
    case ENET_EVENT_TYPE_RECEIVE:
      switch (get_packet_type(event.packet))
      {
      case E_SERVER_TO_CLIENT_NEW_ENTITY:
        on_new_entity_packet(event.packet);
        break;
      case E_SERVER_TO_CLIENT_SET_CONTROLLED_ENTITY:
        on_set_controlled_entity(event.packet);
        break;
      case E_SERVER_TO_CLIENT_SNAPSHOT:
        on_snapshot(event.packet);
        break;
      case E_SERVER_TO_CLIENT_TIME_MSEC:
        on_time(event.packet, event.peer);
        break;
      };
      enet_packet_destroy(event.packet);
      break;
    default:
      break;
    };
  }
}

static void simulate_world(ENetPeer* serverPeer)
{
  if (my_entity != invalid_entity)
  {
    bool left = IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_RIGHT);
    bool up = IsKeyDown(KEY_UP);
    bool down = IsKeyDown(KEY_DOWN);
    get_entity(my_entity, [&](Entity& e)
    {
        // Update
        float thr = (up ? 1.f : 0.f) + (down ? -1.f : 0.f);
        float steer = (left ? -1.f : 0.f) + (right ? 1.f : 0.f);

        // Send
        send_entity_input(serverPeer, my_entity, thr, steer, currentServerTick);
    });
  }
}

static void draw_world(const Camera2D& camera)
{
  BeginDrawing();
    ClearBackground(GRAY);
    BeginMode2D(camera);

      for (const Entity &e : entities)
        draw_entity(e);

    EndMode2D();
  EndDrawing();
}

int main(int argc, const char **argv)
{
  if (enet_initialize() != 0)
  {
    printf("Cannot init ENet");
    return 1;
  }

  ENetHost *client = enet_host_create(nullptr, 1, 2, 0, 0);
  if (!client)
  {
    printf("Cannot create ENet client\n");
    return 1;
  }

  ENetAddress address;
  enet_address_set_host(&address, "localhost");
  address.port = 10131;

  ENetPeer *serverPeer = enet_host_connect(client, &address, 2, 0);
  if (!serverPeer)
  {
    printf("Cannot connect to server");
    return 1;
  }

  int width = 600;
  int height = 600;

  InitWindow(width, height, "w5 networked MIPT");

  const int scrWidth = GetMonitorWidth(0);
  const int scrHeight = GetMonitorHeight(0);
  if (scrWidth < width || scrHeight < height)
  {
    width = std::min(scrWidth, width);
    height = std::min(scrHeight - 150, height);
    SetWindowSize(width, height);
  }

  Camera2D camera = { {0, 0}, {0, 0}, 0.f, 1.f };
  camera.target = Vector2{ 0.f, 0.f };
  camera.offset = Vector2{ width * 0.5f, height * 0.5f };
  camera.rotation = 0.f;
  camera.zoom = 10.f;

  SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

  while (!WindowShouldClose())
  {
    float dt = GetFrameTime(); // for future use and making it look smooth

    update_net(client, serverPeer);
    simulate_world(serverPeer);
    draw_world(camera);
    printf("%d\n", enet_time_get());
  }

  CloseWindow();
  return 0;
}
