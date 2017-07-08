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

#define PI 3.14159265

World::World()
{
}

World:: ~World()
{
    for (auto go : m_gameObjects)
    {
        for (auto comp : go->m_Components)
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
		go2->AddComponent(asp2);
		go2->AddComponent(e);
		m_gameObjects.push_back(go2);
	}
    
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
			if (comp->type == "animator")
			{
				auto animator = static_cast<Animator*>(comp);
				auto anim_sprite = animator->getCurrentState();
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
    // TODO: I'm sure this can be done using mod...
    if (anim->currentFrame > anim->frames.size() - 1)
    {
        anim->currentFrame = 0;
        anim->accumulator = 0.0;
    }
}

void World::handlePlayer(GameObject* go, Player* player, double delta)
{
	auto in = InputManagerSingleton::Instance();

	// Dirty find components
	Physics* phys = nullptr;
	Animator* anim = nullptr;
	for (int i = 0; i < go->m_Components.size(); i++)
	{
		if (go->m_Components.at(i)->type == "physics")
		{
			phys = static_cast<Physics*>(go->m_Components.at(i));
		}
		if (go->m_Components.at(i)->type == "animator")
		{
			anim = static_cast<Animator*>(go->m_Components.at(i));
			break;
		}
	}

	switch (player->playerState) {
	case PlayerState::Stand: {
		anim->currentState = "standing";
		phys->dx = 0;
		phys->dy = 0;
		if (in->isKeyDown(SDL_SCANCODE_W)) 
		{
			// One time impulse
			phys->dy += -player->jumpPower;
			player->playerState = PlayerState::Jump;
		} 
		else if (in->isKeyDown(SDL_SCANCODE_S)) 
		{
			player->playerState = PlayerState::Crouch;
		} 
		else if (in->isKeyDown(SDL_SCANCODE_A)) 
		{
			player->playerState = PlayerState::Walk;
		} 
		else if (in->isKeyDown(SDL_SCANCODE_D)) 
		{
			player->playerState = PlayerState::Walk;
		}
		else if (in->isKeyDown(SDL_SCANCODE_Z))
		{
			player->playerState = PlayerState::Celebrate;
		}
		else if (in->isKeyDown(SDL_SCANCODE_X))
		{
			player->playerState = PlayerState::Dead;
		}
		break;
	}
	case PlayerState::Crouch:
		anim->currentState = "crouching";
		if (!in->isKeyDown(SDL_SCANCODE_S)) 
		{
			player->playerState = PlayerState::Stand;
		}
		break;

	case PlayerState::Walk:
		anim->currentState = "walking";
		if (in->isKeyDown(SDL_SCANCODE_A)) 
		{
			phys->dx = -player->walkSpeed;
			if (in->isKeyDown(SDL_SCANCODE_W))
			{
				// One time impulse
				phys->dy += -player->jumpPower;
				player->playerState = PlayerState::Jump;
			}
		} 
		else if (in->isKeyDown(SDL_SCANCODE_D)) 
		{
			phys->dx = player->walkSpeed;
			if (in->isKeyDown(SDL_SCANCODE_W))
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
		if (!in->isKeyDown(SDL_SCANCODE_Z))
		{
			player->playerState = PlayerState::Stand;
		}
		break;

	case PlayerState::Dead:
		anim->currentState = "dead";
		if (!in->isKeyDown(SDL_SCANCODE_X))
		{
			player->playerState = PlayerState::Stand;
		}
		break;
	}
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
	// Gravity
	phys->dy += gravity * delta;

	// Movement
	go->x += phys->dx * delta;
	go->y += phys->dy * delta;

	// Decay
	phys->dx *= 0.99;
	phys->dy *= 0.95;

	// Limits
	if (go->y > 500) {
		go->y = 500;
		phys->dy = 0;
	}

	if (go->y < 0) {
		go->y = 0;
	}
}
