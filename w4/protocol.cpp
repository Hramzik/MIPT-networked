#include "protocol.h"

void send_join(ENetPeer *peer) {

    Bitstream stream;
    stream.write<uint8_t>(E_CLIENT_TO_SERVER_JOIN);

    ENetPacket *packet = enet_packet_create(stream.data.data(), stream.data.size(), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}

void send_new_entity(ENetPeer *peer, const Entity &ent) {

    Bitstream stream;
    stream.write<uint8_t>(E_SERVER_TO_CLIENT_NEW_ENTITY);
    stream.write<Entity>(ent);

    ENetPacket *packet = enet_packet_create(stream.data.data(), stream.data.size(), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}

void send_set_controlled_entity(ENetPeer *peer, uint16_t eid) {

    Bitstream stream;
    stream.write<uint8_t>(E_SERVER_TO_CLIENT_SET_CONTROLLED_ENTITY);
    stream.write<uint16_t>(eid);

    ENetPacket *packet = enet_packet_create(stream.data.data(), stream.data.size(), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}

void send_entity_state(ENetPeer *peer, uint16_t eid, float x, float y, float size) {

    Bitstream stream;
    stream.write<uint8_t>(E_CLIENT_TO_SERVER_STATE);
    stream.write<uint16_t>(eid);
    stream.write<float>(x);
    stream.write<float>(y);
    stream.write<float>(size);

    ENetPacket *packet = enet_packet_create(stream.data.data(), stream.data.size(), ENET_PACKET_FLAG_UNSEQUENCED);
    enet_peer_send(peer, 1, packet);
}

void send_snapshot(ENetPeer *peer, uint16_t eid, float x, float y, float size) {

    Bitstream stream;
    stream.write<uint8_t>(E_SERVER_TO_CLIENT_SNAPSHOT);
    stream.write<uint16_t>(eid);
    stream.write<float>(x);
    stream.write<float>(y);
    stream.write<float>(size);

    ENetPacket *packet = enet_packet_create(stream.data.data(), stream.data.size(), ENET_PACKET_FLAG_UNSEQUENCED);
    enet_peer_send(peer, 1, packet);
}

MessageType get_packet_type(ENetPacket *packet) {

    Bitstream stream;
    stream.data.assign(packet->data, packet->data + packet->dataLength);
    uint8_t type;
    stream.read<uint8_t>(type);

    return static_cast<MessageType>(type);
}

void deserialize_new_entity(ENetPacket *packet, Entity &ent) {

    Bitstream stream;
    stream.data.assign(packet->data, packet->data + packet->dataLength);
    uint8_t type;

    stream.read<uint8_t>(type);
    stream.read<Entity>(ent);
}

void deserialize_set_controlled_entity(ENetPacket *packet, uint16_t &eid) {

    Bitstream stream;
    stream.data.assign(packet->data, packet->data + packet->dataLength);
    uint8_t type;

    stream.read<uint8_t>(type);
    stream.read<uint16_t>(eid);
}

void deserialize_entity_state(ENetPacket *packet, uint16_t &eid, float &x, float &y, float &size) {

    Bitstream stream;
    stream.data.assign(packet->data, packet->data + packet->dataLength);
    uint8_t type;

    stream.read<uint8_t>(type);
    stream.read<uint16_t>(eid);
    stream.read<float>(x);
    stream.read<float>(y);
    stream.read<float>(size);
}

void deserialize_snapshot(ENetPacket *packet, uint16_t &eid, float &x, float &y, float &size) {

    Bitstream stream;
    stream.data.assign(packet->data, packet->data + packet->dataLength);
    uint8_t type;

    stream.read<uint8_t>(type);
    stream.read<uint16_t>(eid);
    stream.read<float>(x);
    stream.read<float>(y);
    stream.read<float>(size);
}

