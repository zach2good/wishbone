#include "World.h"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <iostream>

#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Player.h"

World::World()
{
    // Set world information
    isPaused = false;

    //TODO: Load everything from a JSON file
    // TODO: Write a pool to hold all components and game objects
  // Create World
  GameObject* go = new GameObject("player", 50, 500);

  Player* p = new Player();
  
  Sprite* p1 = new Sprite("player", 0, 0, 16, 16, 0);
  Sprite* p2 = new Sprite("player", 16, 0, 16, 16, 1);
  Sprite* p3 = new Sprite("player", 32, 0, 16, 16, 2);

  std::vector<Sprite*>* frames = new std::vector<Sprite*>();
  frames->push_back(p1);
  frames->push_back(p2);
  frames->push_back(p3);
  frames->push_back(p2);

  AnimatedSprite* a1 = new AnimatedSprite(150, frames);

  // Push all created components into this vector so they can be deleted later
  m_components.push_back(p);
  m_components.push_back(p1);
  m_components.push_back(p2);
  m_components.push_back(p3);
  m_components.push_back(a1);
  
  go->m_Components.push_back(p);
  go->m_Components.push_back(a1);
  m_gameObjects.push_back(go);
}

World:: ~World()
{
    // TODO: Add logging here
	for (const auto& go : m_gameObjects)
	{
		for (const auto& comp : go->m_Components)
		{
            if (comp)
                delete comp;
		}
        if (go)
            delete go;
	}
    for (const auto& comp : m_components)
    {
        if (comp)
            delete comp;
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
    if (isPaused) { return; }
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		auto go = m_gameObjects.at(i);
		if (!go) return;
		for (int j = 0; j < go->m_Components.size(); j++)
		{
			auto comp = go->m_Components[j];
			if (!comp) return;
			if (comp->type == "anim_sprite")
			{
				auto anim_sprite = static_cast<AnimatedSprite*>(comp);
				updateAnimatedSprite(go, anim_sprite, delta);
			}
            if (comp->type == "player")
            {
                auto player = static_cast<Player*>(comp);
                handlePlayer(go, player, delta);
            }
            if (comp->type == "enemy")
            {
                // auto enemy = static_cast<Enemy*>(comp);
                // handleEnemy(go, enemy, delta);
            }
            if (comp->type == "physics")
            {
                // auto phys = static_cast<Physics*>(comp);
                // handlePhysics(go, phys, delta);
            }
		}
	}
}

void World::updateAnimatedSprite(GameObject* go, AnimatedSprite* anim, double delta)
{
	anim->accumulator += delta;
	anim->currentFrame = (int)anim->accumulator / (int)anim->frametime;

	// Repeat
	if (anim->currentFrame > anim->frames->size() - 1)
	{
		anim->currentFrame = 0;
		anim->accumulator = 0.0;
	}
}

void World::handlePlayer(GameObject* go, Player* player, double delta)
{   static int sign = 1;
    if (go->x > 800.0f - 16.0f || go->x < 0.0f) sign *= -1;
    go->x += 0.20f * delta * sign;
}
