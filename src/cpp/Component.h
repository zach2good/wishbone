#pragma once

#include <string>
#include <typeinfo>
#include <typeindex>

class GameObject;

class Component
{
	// Shout out to Shannon Gerry for helping with the type stuff
public:
	Component(const std::type_info& ti)
		: ti(ti)
	{
		// ===
	}
	virtual ~Component()
	{
		// ===
	}

	const std::type_info& getType() { return ti; }

	template <typename T>
	const bool IsOfType() {
		return ti == typeid(T);
	}

	GameObject* getParent()
	{
		return parent;
	}

	void setParent(GameObject* _parent)
	{
		parent = _parent;
	}

private:
	
	const std::type_info& ti;
	GameObject* parent;
};