#pragma once

#include <vector>
#include "Component.h"
#include "Sprite.h"

class GameObject
{
 public:
 GameObject(): x(0), y(0) { };
 GameObject(float _x, float _y): x(_x), y(_y) { };

  float x;
  float y;

  Sprite sprite;
  // TODO: Strange Error
  //std::vector<Component>;
};
