#pragma once

#include "Component.h"

class Transform : public Component {

public:

	Transform(float _x, float _y) : Component(typeid(Transform)), x(_x), y(_y) 
	{
		// ===
	};

	virtual ~Transform() {}
//private:

	float x;
	float y;

};