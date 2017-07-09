#pragma once

#include <string>
#include <vector>
#include <unordered_map>

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
		m_mapComponents[std::type_index(comp->getType())] = comp;
	}

	// Returns the first one it finds!
	template <typename T>
	T* GetComponentByTypeOld() {
		for (int i = 0; i < m_Components.size(); i++)
		{
			if (m_Components[i]->IsOfType<T>())
			{
				return dynamic_cast<T*>(m_Components.at(i));
			}
		}
		return nullptr;
	}

	// Experimental
	template <typename T>
	T* GetComponentByType() {
		return m_mapComponents[std::type_index(typeid(T))] ?
			dynamic_cast<T*>(m_mapComponents[std::type_index(typeid(T))]) :
			nullptr;
	}

	// TODO: GetComponentsByType that returns an iterator to multiple components 

//private:
	std::string name;
	float x;
	float y;
	std::vector<Component*> m_Components;
	std::unordered_map<std::type_index, Component*> m_mapComponents;
};