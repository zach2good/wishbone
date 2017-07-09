#pragma once

#include "Component.h"

class Enemy : public Component
{
public:

	Enemy() : Component(typeid(Enemy))
	{
		accumulator = rand() % 1000;
	}

	double accumulator;
};

