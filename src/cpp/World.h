#pragma once

#include <vector>
#include <string>

#include "Component.h"
#include "GameObject.h"

class AnimatedSprite;

class World {
 public:
  
  World();
  ~World();
  
  bool load(std::string filename);
  bool save(std::string filename);
  
  void step(double delta);
  
  // private:
    std::vector<GameObject*> m_gameObjects;
    std::vector<Component*> m_components;

	void updateAnimatedSprite(GameObject* go, AnimatedSprite* anim, double delta);
};
