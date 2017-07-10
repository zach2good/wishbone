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

	~GameObject()
	{
		for (auto& comp : m_Components) {
			delete comp;
		}
	}

	void AddComponent(Component* comp)
	{
		comp->setParent(this);

		m_Components.push_back(comp);

		if (m_ComponentsMap[std::type_index(comp->getType())]) {
			std::cout << "WARNING: A component of this type already exists in this Game Object" << std::endl;
		}
		else {
			m_ComponentsMap[std::type_index(comp->getType())] = comp;
		}

	}

	template <typename T>
	T* GetComponentByTypeVec() {
		for (int i = 0; i < m_vecComponents.size(); i++)
		{
			if (m_vecComponents[i]->IsOfType<T>())
			{
				return dynamic_cast<T*>(m_vecComponents.at(i));
			}
		}
		return nullptr;
	}

	template <typename T>
	T* GetComponentByTypeMap() {
		return m_mapComponents[std::type_index(typeid(T))] ?
			dynamic_cast<T*>(m_ComponentsMap[std::type_index(typeid(T))]) :
			nullptr;
	}

	template <typename T>
	T* GetComponentByTypeDynCast() {
		for (int i = 0; i < m_Components.size(); i++)
		{
			if (auto result = dynamic_cast<T*>(m_Components.at(i))) {
				return result;
			}
		}
		return nullptr;
	}

	template <typename T>
	T* GetComponentByType() {
		return GetComponentByTypeDynCast<T>();
	}

//private:
	std::string name;
	float x;
	float y;
	std::vector<Component*> m_Components;
	std::unordered_map<std::type_index, Component*> m_ComponentsMap;
};