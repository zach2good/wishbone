#include "World.h"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <iostream>

#include "Player.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "Physics.h"
#include "Enemy.h"

#define PI 3.14159265

World::World()
{
}

World:: ~World()
{
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
}

void World::init(ResourceManager *rm)
{
	this->rm = rm;

	// Player
	GameObject* go = new GameObject("player", 50, 500);
	std::vector<Sprite*>* vec = new std::vector<Sprite*>();
	vec->push_back(rm->GetSprite("player2"));
	vec->push_back(rm->GetSprite("player1"));
	vec->push_back(rm->GetSprite("player2"));
	vec->push_back(rm->GetSprite("player3"));
	AnimatedSprite* asp = new AnimatedSprite(200, vec);
	Player* p = new Player();
	Physics* ph = new Physics();
	go->m_Components.push_back(p);
	go->m_Components.push_back(ph);
	go->m_Components.push_back(asp);
	m_gameObjects.push_back(go);
	
	for (size_t i = 0; i < 100; i++)
	{
		GameObject* go2 = new GameObject("enemy", rand() % 800, rand() % 600);
		std::vector<Sprite*>* vec2 = new std::vector<Sprite*>();
		vec2->push_back(rm->GetSprite("eye2"));
		vec2->push_back(rm->GetSprite("eye1"));
		vec2->push_back(rm->GetSprite("eye3"));
		vec2->push_back(rm->GetSprite("eye1"));
		AnimatedSprite* asp2 = new AnimatedSprite(200, vec2);
		Enemy* e = new Enemy();
		go2->m_Components.push_back(asp2);
		go2->m_Components.push_back(e);
		m_gameObjects.push_back(go2);
	}

	// Set world information
	isActive = true;
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
    if (!isActive) { return; }
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
                auto enemy = static_cast<Enemy*>(comp);
                handleEnemy(go, enemy, delta);
            }
            if (comp->type == "physics")
            {
                auto phys = static_cast<Physics*>(comp);
                handlePhysics(go, phys, delta);
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
{
    static int sign = 1;
    if (go->x > 800.0f - 16.0f || go->x < 0.0f) sign *= -1;
    go->x += 0.20f * delta * sign;
}


void World::handleEnemy(GameObject* go, Enemy* em, double delta)
{	
	em->accumulator += delta;
	double param = (em->accumulator + go->y)/10;
	double offset = 200;
	double mult = 100;
	go->y = (sin(param * PI / 180)) * mult + offset;
}

void World::handlePhysics(GameObject* go, Physics* phys, double delta)
{
	double gravity = 9.8;

	go->x += phys->dx * delta;
	go->y += phys->dy * delta - 1;

	//go->y += gravity * delta;

	phys->dx *= 0.9;
	phys->dy *= 0.9;

	if (go->y > 750) go->y = 750;
	if (go->y < 0) go->y = 0;
}
