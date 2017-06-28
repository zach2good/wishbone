#pragma once

#include "Component.h"

class Physics : public Component
{
public:

	Physics()
	{
		type = "physics";
		dx = 0;
		dy = 0;
	}

	double dx;
	double dy;
};

