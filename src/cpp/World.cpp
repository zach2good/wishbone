#include "World.h"

World::World()
{
  GameObject go("player", 20, 20);
  // BoundingBox
  // PlayerControlled
  // ParticleEmitter (particle, shape, decaytime, lifetime)
  Sprite sp("res/jetroid-sprites/player/idle/s01.png", "idle01");
  go.m_Components.push_back(&sp);

  GameObject go1("player2", 50, 20);
  Sprite sp2("res/jetroid-sprites/player/idle/s03.png", "idle03");
  go1.m_Components.push_back(&sp2);
  
  m_gameObjects.push_back(&go);
  m_gameObjects.push_back(&go1);
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
