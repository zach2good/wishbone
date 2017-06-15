#include "World.h"

World::World()
{
  GameObject* go = new GameObject("player", 20, 20);
  // BoundingBox
  // PlayerControlled
  // ParticleEmitter (particle, shape, decaytime, lifetime)
  Sprite* sp = new Sprite("res/jetroid-sprites/player/idle/s01.png", "idle01");
  go->m_Components.push_back(sp);
  
  m_gameObjects.push_back(go);
}

World:: ~World()
{

}
  
bool World::load(std::string filename)
{
	return false;
}

bool World::save(std::string filename)
{
	return false;
}
  
void World::step(double delta)
{

}
