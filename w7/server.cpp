#include <enet/enet.h>
#include <iostream>
#include "entity.h"
#include "protocol.h"
#include "mathUtils.h"
#include <stdlib.h>
#include <cfloat>
#include <vector>
#include <map>
#include <unordered_map>

struct ClientState {
    Entity lastSent;
};

static std::vector<Entity> entities;
static std::map<uint16_t, ENetPeer*> controlledMap;
static std::unordered_map<ENetPeer*, std::unordered_map<uint16_t, ClientState>> clientStates;

constexpr int LOD_LEVELS = 4;
constexpr float LOD_DISTANCES[LOD_LEVELS] = {20.f, 50.f, 100.f, FLT_MAX};
constexpr float LOD_POS_THRESHOLDS[LOD_LEVELS] = {0.1f, 0.5f, 1.0f, 2.0f};
constexpr float LOD_ORI_THRESHOLDS[LOD_LEVELS] = {0.1f, 0.2f, 0.3f, 0.4f};
constexpr int LOD_POS_BITS[LOD_LEVELS] = {16, 12, 8, 6};
constexpr int LOD_ORI_BITS[LOD_LEVELS] = {12, 8, 6, 4};

int get_lod_level(float distance) {
    for (int i = 0; i < LOD_LEVELS; ++i) {
        if (distance <= LOD_DISTANCES[i]) return i;
    }
    return LOD_LEVELS - 1;
}

float wrap_distance(float a, float b, float world_size) {
    float direct = fabs(a - b);
    float wrapped = world_size - direct;
    return fmin(direct, wrapped);
}

void on_join(ENetPacket *packet, ENetPeer *peer, ENetHost *host)
{
  // send all entities
  for (const Entity &ent : entities)
    send_new_entity(peer, ent);

  // find max eid
  uint16_t maxEid = entities.empty() ? invalid_entity : entities[0].eid;
  for (const Entity &e : entities)
    maxEid = std::max(maxEid, e.eid);
  uint16_t newEid = maxEid + 1;
  uint32_t color = 0x000000ff +
                   0x44000000 * (rand() % 4 + 1) +
                   0x00440000 * (rand() % 4 + 1) +
                   0x00004400 * (rand() % 4 + 1);
  float x = (rand() % 4) * 5.f;
  float y = (rand() % 4) * 5.f;
  Entity ent = {color, false, x, y, 0.f, (rand() / RAND_MAX) * 3.141592654f, 0.f, 0.f, 0.f, 0.f, newEid};
  entities.push_back(ent);

  controlledMap[newEid] = peer;


  // send info about new entity to everyone
  for (size_t i = 0; i < host->peerCount; ++i)
    send_new_entity(&host->peers[i], ent);
  // send info about controlled entity
  send_set_controlled_entity(peer, newEid);

  for (const Entity& ent : entities) clientStates[peer][ent.eid] = {ent};
}

void create_server_entity(ENetHost *host)
{
  // find max eid
  uint16_t maxEid = entities.empty() ? invalid_entity : entities[0].eid;
  for (const Entity &e : entities)
    maxEid = std::max(maxEid, e.eid);
  uint16_t newEid = maxEid + 1;
  uint32_t color = 0xff000000 +
                   0x00440000 * (rand() % 5) +
                   0x00004400 * (rand() % 5) +
                   0x00000044 * (rand() % 5);
  float x = rand() % int(worldSize * 2) - worldSize;
  float y = rand() % int(worldSize * 2) - worldSize;
  Entity ent = {color, true, x, y, 0.f, (rand() / RAND_MAX) * 3.141592654f, 0.f, 0.f, 0.f, 0.f, newEid};
  entities.push_back(ent);

  // send info about new entity to everyone
  for (size_t i = 0; i < host->peerCount; ++i)
    send_new_entity(&host->peers[i], ent);
}


void on_input(ENetPacket *packet)
{
  uint16_t eid = invalid_entity;
  float thr = 0.f; float steer = 0.f;
  deserialize_entity_input(packet, eid, thr, steer);
  for (Entity &e : entities)
    if (e.eid == eid)
    {
      e.thr = thr;
      e.steer = steer;
    }
}

static void update_net(ENetHost* server)
{
  ENetEvent event;
  while (enet_host_service(server, &event, 0) > 0)
  {
    switch (event.type)
    {
    case ENET_EVENT_TYPE_CONNECT:
      printf("Connection with %x:%u established\n", event.peer->address.host, event.peer->address.port);
      break;
    case ENET_EVENT_TYPE_RECEIVE:
      switch (get_packet_type(event.packet))
      {
        case E_CLIENT_TO_SERVER_JOIN:
          on_join(event.packet, event.peer, server);
          break;
        case E_CLIENT_TO_SERVER_INPUT:
          on_input(event.packet);
          break;
      };
      enet_packet_destroy(event.packet);
      break;
    default:
      break;
    };
  }
}

static void update_ai(Entity& e, float dt)
{
  // small random chance to enable or disable throttle
  if (rand() % 100 == 0)
    e.thr = e.thr > 0.f ? 0.f : 1.f;
  // small random chance to enable or disable steering
  if (rand() % 10 == 0)
    e.steer = e.steer != 0.f ? 0.f : ((rand() % 2) * 2.f - 1.f);
}

void send_entity_update(ENetPeer* peer, Entity& e, const Entity& lastSent, int lod) {
    float posThreshold = LOD_POS_THRESHOLDS[lod];
    float oriThreshold = LOD_ORI_THRESHOLDS[lod];

    float dx = wrap_distance(e.x, lastSent.x, worldSize);
    float dy = wrap_distance(e.y, lastSent.y, worldSize);
    
    float dori = fabs(e.ori - lastSent.ori);
    dori = fmin(dori, 2*PI - dori);

    if (dx > posThreshold || dy > posThreshold || dori > oriThreshold) {
        send_snapshot(peer, e.eid, e.x, e.y, e.ori, e.vx, e.vy, e.omega,
                     LOD_POS_BITS[lod], LOD_ORI_BITS[lod]);
        clientStates[peer][e.eid] = {e};
    }
}

static void simulate_world(ENetHost* server, float dt) {
    uint32_t currentTime = enet_time_get();
    
    for (Entity& e : entities) {
        if (e.serverControlled)
            update_ai(e, dt);
        
        simulate_entity(e, dt);

        for (size_t i = 0; i < server->peerCount; ++i) {
            ENetPeer* peer = &server->peers[i];
            

            auto controlledIt = std::find_if(controlledMap.begin(), controlledMap.end(),
                [peer](auto& kv) { return kv.second == peer; });
            
            if (controlledIt == controlledMap.end()) continue;
            
            Entity& clientEntity = *std::find_if(entities.begin(), entities.end(),
                [&](Entity& ent) { return ent.eid == controlledIt->first; });

            float dx = wrap_distance(e.x, clientEntity.x, worldSize);
            float dy = wrap_distance(e.y, clientEntity.y, worldSize);
            float distance = sqrtf(dx*dx + dy*dy);
            
            int lod = get_lod_level(distance);
            
            ClientState& state = clientStates[peer][e.eid];
            send_entity_update(peer, e, state.lastSent, lod);
        }
    }
}

static void update_time(ENetHost* server, uint32_t curTime)
{
  // We can send it less often too
  for (size_t i = 0; i < server->peerCount; ++i)
    send_time_msec(&server->peers[i], curTime);
}

int main(int argc, const char **argv)
{
  if (enet_initialize() != 0)
  {
    printf("Cannot init ENet");
    return 1;
  }
  ENetAddress address;

  address.host = ENET_HOST_ANY;
  address.port = 10131;

  ENetHost *server = enet_host_create(&address, 32, 2, 0, 0);

  if (!server)
  {
    printf("Cannot create ENet server\n");
    return 1;
  }

  constexpr size_t numShips = 100;
  for (size_t i = 0; i < numShips; ++i)
    create_server_entity(server);

  uint32_t lastTime = enet_time_get();
  while (true)
  {
    uint32_t curTime = enet_time_get();
    float dt = (curTime - lastTime) * 0.001f;
    lastTime = curTime;

    update_net(server);
    simulate_world(server, dt);
    update_time(server, curTime);
    usleep(10000);
  }

  enet_host_destroy(server);

  atexit(enet_deinitialize);
  return 0;
}


