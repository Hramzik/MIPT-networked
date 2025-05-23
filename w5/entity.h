#pragma once
#include <cstdint>

constexpr uint16_t invalid_entity = -1;
struct Entity
{
  // immutable state
  uint32_t color = 0xff00ffff;

  // mutable state
  float x = 0.f;
  float y = 0.f;
  float vx = 0.f;
  float vy = 0.f;
  float ori = 0.f;
  float omega = 0.f;

  // user input
  float thr = 0.f;
  float steer = 0.f;

  // misc
  uint16_t eid = invalid_entity;
};

constexpr float FIXED_DT = 1.0f / 50.0f;
void simulate_entity(Entity &e, float dt);

