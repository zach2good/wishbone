#pragma once

#include <vector>
#include <glm/vec2.hpp> // glm::vec2

#include "Component.h"

struct Collider {
public:
	// NOTE: Always a rectangle
	//CollisionShape collisionShape;

	Collider(float width, float height, float offsetX = 0.0f, float offsetY = 0.0f) {
		size.x = width;
		size.y = height;

		offset.x = offsetX;
		offset.y = offsetY;
	}

	glm::vec2 size;
	glm::vec2 offset;
};

class Physics : public Component
{
public:

	Physics() : Component(typeid(Physics))
	{
		dx = 0;
		dy = 0;
	}

	void AddCollider(float width, float height, float offsetX = 0.0f, float offsetY = 0.0f) {
		colliders.push_back(Collider(width, height, offsetX, offsetY));
	}
    
    // TODO: Dig out old physics textbooks and find some mechanics equations to model all of this correctly
    // TODO: Collision will also need to be in here, using collision layers, things on the same layer will not collide

	bool useGravity = true;
	bool isColliding = false;

	enum CollisionLayer {
		NoCollide,
		One,
		Two,
		Three,
		Four,
		All
	};
	CollisionLayer collisionLayer = CollisionLayer::All;

    double dx;
	double dy;

    double friction;
    double torque;
    double angularMomentum;

	std::vector<Collider> colliders;
};

