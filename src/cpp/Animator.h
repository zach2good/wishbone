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
	Animator()
	{
		type = "animator";
	}

	void addState(std::string name, AnimatedSprite* state) {
		states[name] = state;
	}

	AnimatedSprite* getState(std::string name) {
		return states[name];
	}

	AnimatedSprite* getCurrentState() {
		return states[currentState];
	}

	std::string currentState;
	std::map<std::string, AnimatedSprite*> states;
};

