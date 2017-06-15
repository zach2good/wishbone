#include "World.h"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "Sprite.h"
#include "AnimatedSprite.h"

World::World()
{
  // Create World
  GameObject* go = new GameObject("player", 50, 500);

  Sprite* p1 = new Sprite("player", 0, 0, 16, 16);
  Sprite* p2 = new Sprite("player", 16, 0, 16, 16);
  Sprite* p3 = new Sprite("player", 32, 0, 16, 16);

  std::vector<Sprite*>* frames = new std::vector<Sprite*>();
  frames->push_back(p1);
  frames->push_back(p2);
  frames->push_back(p3);
  frames->push_back(p2);

  AnimatedSprite* a1 = new AnimatedSprite(150, frames);
  
  go->m_Components.push_back(a1);
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
