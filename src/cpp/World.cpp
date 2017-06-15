#include "World.h"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

World::World()
{
  GameObject* go = new GameObject("player", 20, 20);
  // TODO: Filename, ID, Dimensions
  Sprite* sp = new Sprite("", "player", 0, 0, 16, 16);
  go->m_Components.push_back(sp);
  m_gameObjects.push_back(go);
}

World:: ~World()
{
	for (const auto& go : m_gameObjects)
	{
		for (const auto& comp : go->m_Components)
		{
			delete comp;
		}
		delete go;
	}
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
