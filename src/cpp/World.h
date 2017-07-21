#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Component.h"
#include "GameObject.h"

class AnimatedSprite;
class Player;
class ResourceManager;
class Physics;
class Enemy;
class Camera;

class World {
public:

    World();
    virtual ~World();

	void init(ResourceManager* rm);
    
    bool load(std::string filename);
    bool save(std::string filename);

    void step(double delta);

    //private:
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;

    void updateAnimatedSprite(GameObject* go, AnimatedSprite* anim, double delta);
    void handlePlayer(GameObject* go, Player* player, double delta);
	void handleEnemy(GameObject* go, Enemy* em, double delta);
	void handlePhysics(std::vector<Physics*>& items, double delta);
   
	ResourceManager* rm;

    Camera* camera;

	bool isActive;
};
