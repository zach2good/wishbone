#pragma once

#include "Component.h"
#include <glm/vec2.hpp> // glm::vec2

class Transform : public Component {

public:

	Transform(float _x, float _y) : Component(typeid(Transform))
	{
		position.x = _x;
		position.y = _y;
        rotation = glm::vec2(0.0f, 0.0f);
		scale = glm::vec2(1.0f, 1.0f);
	};

	virtual ~Transform() 
    {
        // ===
    }

//private:

	glm::vec2 position; 
    glm::vec2 rotation;
	glm::vec2 scale;
};