#include "protocol.h"
#include "quantisation.h"
#include <cstring> // memcpy
#include <iostream>

void send_join(ENetPeer *peer)
{
  ENetPacket *packet = enet_packet_create(nullptr, sizeof(uint8_t), ENET_PACKET_FLAG_RELIABLE);
  *packet->data = E_CLIENT_TO_SERVER_JOIN;

  enet_peer_send(peer, 0, packet);
}

void send_new_entity(ENetPeer *peer, const Entity &ent)
{
  ENetPacket *packet = enet_packet_create(nullptr, sizeof(uint8_t) + sizeof(Entity),
                                                   ENET_PACKET_FLAG_RELIABLE);
  uint8_t *ptr = packet->data;
  *ptr = E_SERVER_TO_CLIENT_NEW_ENTITY; ptr += sizeof(uint8_t);
  memcpy(ptr, &ent, sizeof(Entity)); ptr += sizeof(Entity);

  enet_peer_send(peer, 0, packet);
}

void send_set_controlled_entity(ENetPeer *peer, uint16_t eid)
{
  ENetPacket *packet = enet_packet_create(nullptr, sizeof(uint8_t) + sizeof(uint16_t),
                                                   ENET_PACKET_FLAG_RELIABLE);
  uint8_t *ptr = packet->data;
  *ptr = E_SERVER_TO_CLIENT_SET_CONTROLLED_ENTITY; ptr += sizeof(uint8_t);
  memcpy(ptr, &eid, sizeof(uint16_t)); ptr += sizeof(uint16_t);

  enet_peer_send(peer, 0, packet);
}

void send_entity_input(ENetPeer *peer, uint16_t eid, float thr, float steer)
{
  ENetPacket *packet = enet_packet_create(nullptr, sizeof(uint8_t) + sizeof(uint16_t) +
                                                   sizeof(uint8_t),
                                                   ENET_PACKET_FLAG_UNSEQUENCED);
  uint8_t *ptr = packet->data;
  *ptr = E_CLIENT_TO_SERVER_INPUT; ptr += sizeof(uint8_t);
  memcpy(ptr, &eid, sizeof(uint16_t)); ptr += sizeof(uint16_t);
  float4bitsQuantized thrPacked(thr, -1.f, 1.f);
  float4bitsQuantized steerPacked(steer, -1.f, 1.f);
  uint8_t thrSteerPacked = (thrPacked.packedVal << 4) | steerPacked.packedVal;
  memcpy(ptr, &thrSteerPacked, sizeof(uint8_t)); ptr += sizeof(uint8_t);
  /*
  memcpy(ptr, &thrPacked, sizeof(uint8_t)); ptr += sizeof(uint8_t);
  memcpy(ptr, &oriPacked, sizeof(uint8_t)); ptr += sizeof(uint8_t);
  */

  enet_peer_send(peer, 1, packet);
}

typedef PackedFloat<uint16_t, 11> PositionXQuantized;
typedef PackedFloat<uint16_t, 10> PositionYQuantized;

void send_snapshot(ENetPeer* peer, uint16_t eid, float x, float y, float ori, 
    float vx, float vy, float omega, int posBits, int oriBits) 
{
    constexpr float VELOCITY_RANGE = 40.0f;
    constexpr float OMEGA_RANGE = 2*PI;

    uint16_t xPacked = pack_float<uint16_t>(x, -worldSize, worldSize, posBits);
    uint16_t yPacked = pack_float<uint16_t>(y, -worldSize, worldSize, posBits);
    uint16_t oriPacked = pack_float<uint16_t>(ori, 0, 2*PI, oriBits);

    uint8_t vxPacked = pack_float<uint8_t>(vx, -VELOCITY_RANGE, VELOCITY_RANGE, 8);
    uint8_t vyPacked = pack_float<uint8_t>(vy, -VELOCITY_RANGE, VELOCITY_RANGE, 8);
    uint8_t omegaPacked = pack_float<uint8_t>(omega, -OMEGA_RANGE, OMEGA_RANGE, 8);

    ENetPacket* packet = enet_packet_create(nullptr, 
    sizeof(uint8_t) +
    sizeof(uint16_t) +
    sizeof(uint16_t)*2 +
    sizeof(uint16_t) +
    sizeof(uint8_t)*3 +
    sizeof(uint16_t)*2,
    ENET_PACKET_FLAG_UNSEQUENCED);

    uint8_t* ptr = packet->data;

    *ptr++ = E_SERVER_TO_CLIENT_SNAPSHOT;
    memcpy(ptr, &eid, sizeof(uint16_t)); ptr += sizeof(uint16_t);
    memcpy(ptr, &xPacked, sizeof(uint16_t)); ptr += sizeof(uint16_t);
    memcpy(ptr, &yPacked, sizeof(uint16_t)); ptr += sizeof(uint16_t);
    memcpy(ptr, &oriPacked, sizeof(uint16_t)); ptr += sizeof(uint16_t);
    *ptr++ = vxPacked;
    *ptr++ = vyPacked;
    *ptr++ = omegaPacked;
    memcpy(ptr, &posBits, sizeof(uint16_t)); ptr += sizeof(uint16_t);
    memcpy(ptr, &oriBits, sizeof(uint16_t));

    enet_peer_send(peer, 1, packet);
}

void send_time_msec(ENetPeer *peer, uint32_t timeMsec)
{
  ENetPacket *packet = enet_packet_create(nullptr, sizeof(uint8_t) + sizeof(uint32_t),
                                                   ENET_PACKET_FLAG_RELIABLE);
  uint8_t *ptr = packet->data;
  *ptr = E_SERVER_TO_CLIENT_TIME_MSEC; ptr += sizeof(uint8_t);
  memcpy(ptr, &timeMsec, sizeof(uint32_t)); ptr += sizeof(uint32_t);

  enet_peer_send(peer, 0, packet);
}

MessageType get_packet_type(ENetPacket *packet)
{
  return (MessageType)*packet->data;
}

void deserialize_new_entity(ENetPacket *packet, Entity &ent)
{
  uint8_t *ptr = packet->data; ptr += sizeof(uint8_t);
  ent = *(Entity*)(ptr); ptr += sizeof(Entity);
}

void deserialize_set_controlled_entity(ENetPacket *packet, uint16_t &eid)
{
  uint8_t *ptr = packet->data; ptr += sizeof(uint8_t);
  eid = *(uint16_t*)(ptr); ptr += sizeof(uint16_t);
}

void deserialize_entity_input(ENetPacket *packet, uint16_t &eid, float &thr, float &steer)
{
  uint8_t *ptr = packet->data; ptr += sizeof(uint8_t);
  eid = *(uint16_t*)(ptr); ptr += sizeof(uint16_t);
  uint8_t thrSteerPacked = *(uint8_t*)(ptr); ptr += sizeof(uint8_t);
  /*
  uint8_t thrPacked = *(uint8_t*)(ptr); ptr += sizeof(uint8_t);
  uint8_t oriPacked = *(uint8_t*)(ptr); ptr += sizeof(uint8_t);
  */
  static uint8_t neutralPackedValue = pack_float<uint8_t>(0.f, -1.f, 1.f, 4);
  static uint8_t nominalPackedValue = pack_float<uint8_t>(1.f, 0.f, 1.2f, 4);
  float4bitsQuantized thrPacked(thrSteerPacked >> 4);
  float4bitsQuantized steerPacked(thrSteerPacked & 0x0f);
  thr = thrPacked.packedVal == neutralPackedValue ? 0.f : thrPacked.unpack(-1.f, 1.f);
  steer = steerPacked.packedVal == neutralPackedValue ? 0.f : steerPacked.unpack(-1.f, 1.f);
}

void send_ack(ENetPeer* peer, uint16_t eid)
{
    ENetPacket* packet = enet_packet_create(nullptr, 
        sizeof(uint8_t) + sizeof(uint16_t),
        ENET_PACKET_FLAG_RELIABLE);
        
    uint8_t* ptr = packet->data;
    *ptr++ = E_CLIENT_TO_SERVER_ACK;
    memcpy(ptr, &eid, sizeof(uint16_t));
    
    enet_peer_send(peer, 0, packet);
}

void deserialize_snapshot(ENetPacket* packet, uint16_t& eid, float& x, float& y,
    float& ori, float& vx, float& vy, float& omega)
{
    uint8_t* ptr = packet->data;
    ptr += sizeof(uint8_t); // Skip message type

    memcpy(&eid, ptr, sizeof(uint16_t)); ptr += sizeof(uint16_t);

    uint16_t xPacked, yPacked, oriPacked;
    memcpy(&xPacked, ptr, sizeof(uint16_t)); ptr += sizeof(uint16_t);
    memcpy(&yPacked, ptr, sizeof(uint16_t)); ptr += sizeof(uint16_t);
    memcpy(&oriPacked, ptr, sizeof(uint16_t)); ptr += sizeof(uint16_t);

    uint8_t vxPacked = *ptr++;
    uint8_t vyPacked = *ptr++;
    uint8_t omegaPacked = *ptr++;

    uint16_t posBits, oriBits;
    memcpy(&posBits, ptr, sizeof(uint16_t)); ptr += sizeof(uint16_t);
    memcpy(&oriBits, ptr, sizeof(uint16_t));

    x = unpack_float<uint16_t>(xPacked, -worldSize, worldSize, posBits);
    y = unpack_float<uint16_t>(yPacked, -worldSize, worldSize, posBits);
    ori = unpack_float<uint16_t>(oriPacked, 0, 2*PI, oriBits);

    vx = unpack_float<uint8_t>(vxPacked, -40.0f, 40.0f, 8);
    vy = unpack_float<uint8_t>(vyPacked, -40.0f, 40.0f, 8);
    omega = unpack_float<uint8_t>(omegaPacked, -PI, PI, 8);
}

void deserialize_time_msec(ENetPacket *packet, uint32_t &timeMsec)
{
  uint8_t *ptr = packet->data; ptr += sizeof(uint8_t);
  timeMsec = *(uint32_t*)(ptr); ptr += sizeof(uint32_t);
}

