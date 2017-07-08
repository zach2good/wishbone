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
		ddx = 0;
		ddy = 0;
	}
    
    // TODO: Dig out old physics textbooks and find some mechanics equations to model all of this correctly
    // TODO: Collision will also need to be in here, using collision layers, things on the same layer will not collide

    double dx;
	double dy;
    
    double ddx;
    double ddy;

    double friction;
    double torque;
    double angularMomentum;

    // AABB aabb;
    // CollisionShape Square?
};

