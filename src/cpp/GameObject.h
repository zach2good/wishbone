#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Sprite.h"

class GameObject
{
public:
	GameObject(std::string _name) : name(_name), x(0), y(0) { };
	GameObject(std::string _name, float _x, float _y) : name(_name), x(_x), y(_y) { };

	std::string name;
	float x;
	float y;

	std::vector<Component*> m_Components;
};
