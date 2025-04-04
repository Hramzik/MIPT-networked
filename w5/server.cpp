#include <enet/enet.h>
#include <iostream>
#include "entity.h"
#include "protocol.h"
#include "mathUtils.h"
#include <stdlib.h>
#include <vector>
#include <map>

constexpr uint32_t MAX_TICKS_PER_FRAME = 10;

static std::vector<Entity> entities;
static std::map<uint16_t, ENetPeer*> controlledMap;
uint32_t currentTick = 0;

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
  uint32_t color = 0xff000000 +
                   0x00440000 * (rand() % 5) +
                   0x00004400 * (rand() % 5) +
                   0x00000044 * (rand() % 5);
  float x = (rand() % 4) * 5.f;
  float y = (rand() % 4) * 5.f;
  Entity ent = {color, x, y, 0.f, (rand() / RAND_MAX) * 3.141592654f, 0.f, 0.f, 0.f, 0.f, newEid};
  entities.push_back(ent);

  controlledMap[newEid] = peer;


  // send info about new entity to everyone
  for (size_t i = 0; i < host->peerCount; ++i)
    send_new_entity(&host->peers[i], ent);
  // send info about controlled entity
  send_set_controlled_entity(peer, newEid);
}

void on_input(ENetPacket *packet) {
    uint16_t eid;
    float thr, steer;
    uint32_t tick;
    deserialize_entity_input(packet, eid, thr, steer, tick);

    // в будущем можно игнорировать старые пакеты
    // if (tick + C < currentTick) {
    //     return;
    // }

    for (Entity &e : entities) {
        if (e.eid == eid) {
            e.thr = thr;
            e.steer = steer;
        }
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

static void simulate_world(ENetHost* server, float dt) {
    uint32_t curTime = enet_time_get();
    for (Entity &e : entities) {
        simulate_entity(e, dt);
        for (size_t i = 0; i < server->peerCount; ++i) {
            ENetPeer *peer = &server->peers[i];
            send_snapshot(peer, e.eid, e.x, e.y, e.ori, e.vx, e.vy, e.omega, curTime, currentTick);
        }
    }
}

static void update_time(ENetHost* server, uint32_t curTime, uint32_t currentTick) {
    for (size_t i = 0; i < server->peerCount; ++i) {
        send_time_msec(&server->peers[i], curTime, currentTick);
    }
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

  uint32_t lastTime = enet_time_get();
    float accumulator = 0.0f; // Накопитель времени

    while (true) {
        uint32_t curTime = enet_time_get();
        float frameTime = (curTime - lastTime) * 0.001f;
        lastTime = curTime;

        frameTime = std::min(frameTime, 0.25f);

        accumulator += frameTime;

        int ticksProcessed = 0;
        while (accumulator >= FIXED_DT && ticksProcessed < MAX_TICKS_PER_FRAME) {
            update_net(server);
            simulate_world(server, FIXED_DT);
            accumulator -= FIXED_DT;
            currentTick++;
            ticksProcessed++;
        }

        update_time(server, curTime, currentTick);
        usleep(1000);
    }

  enet_host_destroy(server);

  atexit(enet_deinitialize);
  return 0;
}


