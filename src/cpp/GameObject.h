#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>

#include "Component.h"

class GameObject {
public:
	GameObject(std::string _name) : name(_name), x(0), y(0) {};
	GameObject(std::string _name, float _x, float _y)
		: name(_name), x(_x), y(_y) {};

	~GameObject()
	{
		// ===
	}

	void AddComponent(std::shared_ptr<Component> comp)
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
	void RemoveComponent()
	{
		for (int i = 0; i < m_Components.size(); i++)
		{
			if (m_Components[i]->IsOfType<T>())
			{
				m_Components.erase(m_Components.begin() + i);
			}
		}

		m_ComponentsMap.erase(std::type_index(typeid(T)));
	}

	template <typename T>
	T* GetComponentByTypeVec() {
		for (int i = 0; i < m_Components.size(); i++)
		{
			if (m_Components[i]->IsOfType<T>())
			{
				return dynamic_cast<T*>(m_Components.at(i).get());
			}
		}
		return nullptr;
	}

	template <typename T>
	T* GetComponentByTypeMap() {
		return m_ComponentsMap[std::type_index(typeid(T))] ?
			dynamic_cast<T*>(m_ComponentsMap[std::type_index(typeid(T))].get()) :
			nullptr;
	}

	template <typename T>
	T* GetComponentByTypeDynCast() {
		for (int i = 0; i < m_Components.size(); i++)
		{
			if (auto result = dynamic_cast<T*>(m_Components.at(i).get())) {
				return result;
			}
		}
		return nullptr;
	}

	template <typename T>
	T* GetComponentByType() {
		return GetComponentByTypeDynCast<T>();
	}

    void AddChild(std::shared_ptr<GameObject> go)
    {
        // Does it already exist in this object?

        // Insert
        m_Children.push_back(go);
    }

    std::shared_ptr<GameObject> GetChild()
    {
        // TODO
    }
    
    void RemoveChild()
    {
        // TODO
    }
    
//private:
	std::string name;
	// TODO: Make a decent system for generating non-clasing GUIDs
	short id = rand() % 32000;

	// TODO: Move x, y, z etc. into a transform component
	float x;
	float y;

	// TODO: Decide on a single system and stick to it, instead of using 2
	std::vector<std::shared_ptr<Component>> m_Components;
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_ComponentsMap;

    std::vector<std::shared_ptr<GameObject>> m_Children;
};
