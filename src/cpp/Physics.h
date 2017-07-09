#pragma once

#include "Component.h"

enum CollisionLayer {
	NoCollide,
	One,
	Two,
	Three,
	Four,
	All
};

class Physics : public Component
{
public:

	Physics() : Component(typeid(Physics))
	{
		dx = 0;
		dy = 0;
		ddx = 0;
		ddy = 0;
	}
    
    // TODO: Dig out old physics textbooks and find some mechanics equations to model all of this correctly
    // TODO: Collision will also need to be in here, using collision layers, things on the same layer will not collide

	bool useGravity = true;
	bool isColliding = false;
	CollisionLayer layer = CollisionLayer::All;

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

