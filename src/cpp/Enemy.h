#pragma once

#include "Component.h"

class Enemy : public Component
{
public:

	Enemy()
	{
		type = "enemy";
		accumulator = rand() % 1000;
	}

	double accumulator;
};

