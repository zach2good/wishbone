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
#include "InputManager.h"
#include "Animator.h"
#include "SoundManager.h"

#define PI 3.14159265

World::World()
{
}

World:: ~World()
{
	for (auto go : m_gameObjects)
	{
		if (go)
			delete go;
	}
}

void World::init(ResourceManager *rm)
{
	this->rm = rm;

	// Load Map
	auto map = rm->map->layerMap["bg"];
	for (int i = 0; i < map.data.size(); i++)
	{
		if (map.data[i] == 0) continue;
		GameObject* block = new GameObject("bg_mapblock", (i % map.width) * mapSize, (i / map.width) * mapSize);
		std::string tileString = "tile" + std::to_string(map.data[i]);
		AnimatedSprite* block_tile = new AnimatedSprite(200, 1, rm->GetSprite(tileString));
		block->AddComponent(block_tile);
		m_gameObjects.push_back(block);
	}

	map = rm->map->layerMap["main"];
	for (int i = 0; i < map.data.size(); i++)
	{
		if (map.data[i] == 0) continue;
		GameObject* block = new GameObject("main_mapblock", (i % map.width) * mapSize, (i / map.width) * mapSize);
		std::string tileString = "tile" + std::to_string(map.data[i]);
		AnimatedSprite* block_tile = new AnimatedSprite(200, 1, rm->GetSprite(tileString));
		block->AddComponent(block_tile);
		m_gameObjects.push_back(block);
	}

	// Enemies
	for (size_t i = 0; i < 100; i++)
	{
		GameObject* go2 = new GameObject("enemy", rand() % 800, rand() % 600);
		AnimatedSprite* asp2 = new AnimatedSprite(200,
			4,
			rm->GetSprite("eye2"),
			rm->GetSprite("eye1"),
			rm->GetSprite("eye3"),
			rm->GetSprite("eye1"));
		Enemy* e = new Enemy();
		Physics* phe = new Physics();
		phe->collisionLayer = Physics::CollisionLayer::One;
		phe->useGravity = false;
		go2->AddComponent(phe);
		go2->AddComponent(asp2);
		go2->AddComponent(e);
		m_gameObjects.push_back(go2);
	}

	// Player
	GameObject* go = new GameObject("player", 50, 500);
	AnimatedSprite* walking = new AnimatedSprite(200,
		4,
		rm->GetSprite("player2"),
		rm->GetSprite("player1"),
		rm->GetSprite("player2"),
		rm->GetSprite("player3"));

	AnimatedSprite* standing = new AnimatedSprite(200, 1, rm->GetSprite("player6"));
	AnimatedSprite* crouching = new AnimatedSprite(200, 1, rm->GetSprite("player4"));
	AnimatedSprite* jumping = new AnimatedSprite(200, 1, rm->GetSprite("player5"));
	AnimatedSprite* celebrating = new AnimatedSprite(400, 2, rm->GetSprite("player7"), rm->GetSprite("player6"));
	AnimatedSprite* dead = new AnimatedSprite(200, 1, rm->GetSprite("player8"));
	Animator* playerAnimator = new Animator();
	playerAnimator->addState("walking", walking);
	playerAnimator->addState("standing", standing);
	playerAnimator->addState("crouching", crouching);
	playerAnimator->addState("jumping", jumping);
	playerAnimator->addState("celebrating", celebrating);
	playerAnimator->addState("dead", dead);
	playerAnimator->currentState = "standing";
	Player* p = new Player();
	Physics* ph = new Physics();
	go->AddComponent(p);
	go->AddComponent(ph);
	go->AddComponent(playerAnimator);
	m_gameObjects.push_back(go);

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
		auto go = m_gameObjects.at(i);
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
		auto go = m_gameObjects.at(i);
		if (!go) return;
		for (int j = 0; j < go->m_Components.size(); j++)
		{
			auto comp = go->m_Components[j];
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
	Animator* anim = go->GetComponentByType<Animator>();;

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

				auto parentA = itemA->getParent();
				auto parentB = itemB->getParent();

				if (itemA == itemB ||
					itemA->collisionLayer != Physics::CollisionLayer::All &&
					itemB->collisionLayer != Physics::CollisionLayer::All &&
					itemA->collisionLayer == itemB->collisionLayer) 
				{
					continue;
				}

				int spriteW = 100;
				int spriteH = 100;

				// Check collision
				if (parentA->x < parentB->x + spriteW &&
					parentA->x + spriteW > parentB->x &&
					parentA->y < parentB->y + spriteH &&
					parentA->y + spriteH > parentB->y)
				{
					itemA->isColliding = true;
					itemB->isColliding = true;
				}
			}
		}
	}
}
