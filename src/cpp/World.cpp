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

World::World()
{
    ResourceManager rm = ResourceManager::Instance();

    //TODO: Load everything from a JSON file
    // TODO: Write a pool to hold all components and game objects
    // Create World
    GameObject* go = new GameObject("player", 50, 500);

    Sprite* sp = rm.GetSprite("player");

    Player* p = new Player();

    go->m_Components.push_back(p);
    go->m_Components.push_back(sp);

    m_gameObjects.push_back(go);

    // Set world information
    isActive = true;
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
    // TODO: Do I really want a singleton? Its not that big a deal to just create the resource manager and pass it around...

    ResourceManager rm = ResourceManager::Instance();

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
{
    static int sign = 1;
    if (go->x > 800.0f - 16.0f || go->x < 0.0f) sign *= -1;
    go->x += 0.20f * delta * sign;
}
