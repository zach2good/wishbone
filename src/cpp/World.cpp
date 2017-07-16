#include "World.h"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <iostream>
#include <memory>

#include "Player.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "Physics.h"
#include "Enemy.h"
#include "InputManager.h"
#include "Animator.h"
#include "SoundManager.h"

#define PI 3.14159265

World::World()
{
	// ===
}

World:: ~World()
{
	// ===
}

void World::init(ResourceManager *rm)
{
	this->rm = rm;

	// Load Map
	auto map = rm->map->layerMap["bg"];
	for (int i = 0; i < map.data.size(); i++)
	{
		if (map.data[i] == 0) continue;
		auto block = std::make_shared<GameObject>("bg_mapblock", (i % map.width) * mapSize, (i / map.width) * mapSize);
		std::string tileString = "tile" + std::to_string(map.data[i]);
		auto block_tile = std::make_shared<AnimatedSprite>(200, 1, rm->GetSprite(tileString));
		block->AddComponent(block_tile);
		m_gameObjects.push_back(block);
	}
	
	map = rm->map->layerMap["main"];
	for (int i = 0; i < map.data.size(); i++)
	{
		if (map.data[i] == 0) continue;
		auto block = std::make_shared<GameObject>("main_mapblock", (i % map.width) * mapSize, (i / map.width) * mapSize);
		std::string tileString = "tile" + std::to_string(map.data[i]);
		auto block_tile = std::make_shared<AnimatedSprite>(200, 1, rm->GetSprite(tileString));
		block->AddComponent(block_tile);
		m_gameObjects.push_back(block);
	}
	
	// Enemies
	for (size_t i = 0; i < 100; i++)
	{
		auto go = std::make_shared<GameObject>("enemy", rand() % 800, rand() % 600);
		auto asp = std::make_shared<AnimatedSprite>(200,
			4,
			rm->GetSprite("eye2"),
			rm->GetSprite("eye1"),
			rm->GetSprite("eye3"),
			rm->GetSprite("eye1"));

		auto e = std::make_shared<Enemy>();

		auto phe = std::make_shared<Physics>();
		phe->collisionLayer = Physics::CollisionLayer::One;
		phe->useGravity = false;
		phe->AddCollider(100, 100);

		go->AddComponent(phe);
		go->AddComponent(asp);
		go->AddComponent(e);

		m_gameObjects.push_back(go);
	}

	// Player
	{
		auto go = std::make_shared<GameObject>("player", 50, 500);

		auto walking = std::make_shared<AnimatedSprite>(200,
			4,
			rm->GetSprite("player2"),
			rm->GetSprite("player1"),
			rm->GetSprite("player2"),
			rm->GetSprite("player3"));

		auto standing = std::make_shared<AnimatedSprite>(200, 1, rm->GetSprite("player6"));
		auto crouching = std::make_shared<AnimatedSprite>(200, 1, rm->GetSprite("player4"));
		auto jumping = std::make_shared<AnimatedSprite>(200, 1, rm->GetSprite("player5"));
		auto celebrating = std::make_shared<AnimatedSprite>(400, 2, rm->GetSprite("player7"), rm->GetSprite("player6"));
		auto dead = std::make_shared<AnimatedSprite>(200, 1, rm->GetSprite("player8"));

		auto playerAnimator = std::make_shared<Animator>();
		playerAnimator->addState("walking", walking);
		playerAnimator->addState("standing", standing);
		playerAnimator->addState("crouching", crouching);
		playerAnimator->addState("jumping", jumping);
		playerAnimator->addState("celebrating", celebrating);
		playerAnimator->addState("dead", dead);
		playerAnimator->currentState = "standing";

		auto p = std::make_shared<Player>();

		auto ph = std::make_shared<Physics>();
		ph->AddCollider(100, 100);

		go->AddComponent(p);
		go->AddComponent(ph);
		go->AddComponent(playerAnimator);

		m_gameObjects.push_back(go);
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

	// Sorting and filtering
	physicsItems.clear();
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		auto go = m_gameObjects.at(i).get();
		if (!go) return;
		Physics* phys = go->GetComponentByType<Physics>();
		if (phys)
		{
			phys->isColliding = false;
			physicsItems.push_back(phys);
		}
	}
	handlePhysics(physicsItems, delta);

	// Actions
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		auto go = m_gameObjects.at(i).get();
		if (!go) return;
		for (int j = 0; j < go->m_Components.size(); j++)
		{
			auto comp = go->m_Components[j].get();
			if (!comp) return;
			if (comp->IsOfType<AnimatedSprite>())
			{
				auto anim_sprite = static_cast<AnimatedSprite*>(comp);
				updateAnimatedSprite(go, anim_sprite, delta);
			}
			if (comp->IsOfType<Animator>())
			{
				auto animator = static_cast<Animator*>(comp);
				auto anim_sprite = animator->getCurrentState();
				updateAnimatedSprite(go, anim_sprite, delta);
			}
			if (comp->IsOfType<Player>())
			{
				auto player = static_cast<Player*>(comp);
				handlePlayer(go, player, delta);
			}
			if (comp->IsOfType<Enemy>())
			{
				auto enemy = static_cast<Enemy*>(comp);
				handleEnemy(go, enemy, delta);
			}
		}
	}
}

void World::updateAnimatedSprite(GameObject* go, AnimatedSprite* anim, double delta)
{
	anim->accumulator += delta;
	anim->currentFrame = (int)anim->accumulator / (int)anim->frametime;

	// Repeat
	// TODO: I'm sure this can be done using mod...
	if (anim->currentFrame > anim->frames.size() - 1)
	{
		anim->currentFrame = 0;
		anim->accumulator = 0.0;
	}
}

void World::handlePlayer(GameObject* go, Player* player, double delta)
{
	// Dirty find components
	Physics* phys = go->GetComponentByType<Physics>();
	Animator* anim = go->GetComponentByType<Animator>();

	if (phys->isColliding) {
		phys->dy += -player->jumpPower * 0.25;
		phys->dx = 0;
		phys->collisionLayer = Physics::CollisionLayer::NoCollide;
		gSound.Play("laser");
		player->playerState = PlayerState::Dead;
	}

	switch (player->playerState) {
	case PlayerState::Stand: {
		anim->currentState = "standing";
		phys->dx = 0;
		phys->dy = 0;
		if (gInput.isKeyDown(SDL_SCANCODE_W))
		{
			// One time impulse
			phys->dy += -player->jumpPower;
			gSound.Play("jump");
			player->playerState = PlayerState::Jump;
		}
		else if (gInput.isKeyDown(SDL_SCANCODE_S))
		{
			player->playerState = PlayerState::Crouch;
		}
		else if (gInput.isKeyDown(SDL_SCANCODE_A))
		{
			player->playerState = PlayerState::Walk;
		}
		else if (gInput.isKeyDown(SDL_SCANCODE_D))
		{
			player->playerState = PlayerState::Walk;
		}
		else if (gInput.isKeyDown(SDL_SCANCODE_Z))
		{
			player->playerState = PlayerState::Celebrate;
		}
		else if (gInput.isKeyDown(SDL_SCANCODE_X))
		{
			//player->playerState = PlayerState::Dead;
		}
		break;
	}
	case PlayerState::Crouch:
		anim->currentState = "crouching";
		if (!gInput.isKeyDown(SDL_SCANCODE_S))
		{
			player->playerState = PlayerState::Stand;
		}
		break;

	case PlayerState::Walk:
		anim->currentState = "walking";
		if (gInput.isKeyDown(SDL_SCANCODE_A))
		{
			phys->dx = -player->walkSpeed;
			if (gInput.isKeyDown(SDL_SCANCODE_W))
			{
				// One time impulse
				phys->dy += -player->jumpPower;
				player->playerState = PlayerState::Jump;
			}
		}
		else if (gInput.isKeyDown(SDL_SCANCODE_D))
		{
			phys->dx = player->walkSpeed;
			if (gInput.isKeyDown(SDL_SCANCODE_W))
			{
				// One time impulse
				phys->dy += -player->jumpPower;
				player->playerState = PlayerState::Jump;
			}
		}
		else
		{
			player->playerState = PlayerState::Stand;
		}

		break;

	case PlayerState::Jump:
		anim->currentState = "jumping";
		if (go->y >= 500)
		{
			player->playerState = PlayerState::Stand;
		}
		break;

	case PlayerState::Fall:
		player->playerState = PlayerState::Stand;
		break;

	case PlayerState::GrabLedge:
		break;

	case PlayerState::Celebrate:
		anim->currentState = "celebrating";
		if (!gInput.isKeyDown(SDL_SCANCODE_Z))
		{
			player->playerState = PlayerState::Stand;
		}
		break;

	case PlayerState::Dead:
		anim->currentState = "dead";
		if (gInput.isKeyDown(SDL_SCANCODE_X))
		{
			phys->collisionLayer = Physics::CollisionLayer::All;
			gSound.Play("pickup");
			player->playerState = PlayerState::Stand;
		}
		break;
	}
}

void World::handleEnemy(GameObject* go, Enemy* em, double delta)
{
	em->accumulator += delta;
	double param = (em->accumulator + go->y) / 10;
	double offset = 200;
	double mult = 100;
	go->y = (sin(param * PI / 180)) * mult + offset;
}

void World::handlePhysics(std::vector<Physics*>& items, double delta)
{
	for (auto& item : items) {
		auto phys = item;
		auto go = phys->getParent();

		// Gravity
		if (phys->useGravity)
			phys->dy += gravity * delta;

		// Movement
		go->x += phys->dx * delta;
		go->y += phys->dy * delta;

		// Decay
		phys->dx *= 0.99;
		phys->dy *= 0.95;

		// Limits
		// TEMP
		// Ground
		if (go->y > 500) {
			go->y = 500;
			phys->dy = 0;
		}
		// Ceiling
		if (go->y < 0) {
			go->y = 0;
		}

		if (go->x > 750) {
			go->x = 750;
			phys->dx = 0;
		}
		if (go->x < 0) {
			go->x = 0;
			phys->dx = 0;
		}

		// Collision (Brute Force)
		for (int i = 0; i < physicsItems.size(); i++)
		{
			for (int j = 0; j < physicsItems.size(); j++)
			{
				auto itemA = physicsItems[i];
				auto itemB = physicsItems[j];

				if (itemA->collisionLayer == Physics::CollisionLayer::NoCollide ||
					itemB->collisionLayer == Physics::CollisionLayer::NoCollide)
				{
					continue;
				}

				if (itemA == itemB ||
					itemA->collisionLayer != Physics::CollisionLayer::All &&
					itemB->collisionLayer != Physics::CollisionLayer::All &&
					itemA->collisionLayer == itemB->collisionLayer) 
				{
					continue;
				}

				int spriteW = 100;
				int spriteH = 100;

				auto parentA = itemA->getParent();
				auto parentB = itemB->getParent();	

				for (int a = 0; a < itemA->colliders.size(); a++)
				{
					for (int b = 0; b < itemB->colliders.size(); b++)
					{
						if (itemA->isColliding || itemB->isColliding)
						{
							return;
						}

						auto& colA = itemA->colliders.at(a);
						auto& colB = itemB->colliders.at(a);

						// ===
						colA.offset.x = parentA->x;
						colA.offset.y = parentA->y;

						colB.offset.x = parentB->x;
						colB.offset.y = parentB->y;

						// ===
						if (colA.offset.x < colB.offset.x + colB.size.x &&
							colA.offset.x + colA.size.x > colB.offset.x &&
							colA.offset.y < colB.offset.y + colB.size.y &&
							colA.offset.y + colA.size.y > colB.offset.y)
						{
							itemA->isColliding = true;
							itemB->isColliding = true;
							continue;
						}
					}
				}

				/*
				// Check collision
				if (parentA->x < parentB->x + spriteW &&
					parentA->x + spriteW > parentB->x &&
					parentA->y < parentB->y + spriteH &&
					parentA->y + spriteH > parentB->y)
				{
					itemA->isColliding = true;
					itemB->isColliding = true;
				}
				*/
			}
		}
	}
}
