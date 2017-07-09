#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Sprite.h"

class GameObject {
public:
	GameObject(std::string _name) : name(_name), x(0), y(0) {};
	GameObject(std::string _name, float _x, float _y)
		: name(_name), x(_x), y(_y) {};

	void AddComponent(Component* comp)
	{
		comp->setParent(this);
		m_Components.push_back(comp);
	}

	template <typename T>
	T* GetComponentByType() {
		for (int i = 0; i < m_Components.size(); i++)
		{
			if (m_Components[i]->IsOfType<T>())
			{
				return static_cast<T*>(m_Components.at(i));
			}
		}
	}

//private:
	std::string name;
	float x;
	float y;
	std::vector<Component*> m_Components;
};