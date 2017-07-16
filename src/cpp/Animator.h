#pragma once

#include <string>
#include <vector>
#include <map>
#include <stdarg.h>  

#include "Component.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

class Animator : public Component
{
public:
	Animator() : Component(typeid(Animator))
	{
	}

	~Animator()
	{
		// ===
	}

	void addState(std::string name, std::shared_ptr<AnimatedSprite> state) {
		states[name] = state;
	}

	AnimatedSprite* getState(std::string name) {
		return states[name].get();
	}

	AnimatedSprite* getCurrentState() {
		return states[currentState].get();
	}

	std::string currentState;
	std::map<std::string, std::shared_ptr<AnimatedSprite>> states;
};

