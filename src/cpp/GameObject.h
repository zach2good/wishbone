#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Sprite.h"

class GameObject {
public:
    GameObject(std::string _name) : name(_name), x(0), y(0) {};
    GameObject(std::string _name, float _x, float _y)
        : name(_name), x(_x), y(_y){};

    std::string name;
    float x;
    float y;

    void AddComponent(Component* comp)
    {
        comp->parent = this;
        m_Components.push_back(comp);
    }

    // TODO: Write this, consumer will have to cast the resulting object up themselves
    // unless there is a way to return different types in newer versions of C++?
    
    //template T
    //Component* GetComponent<T>
    
    //private:
    std::vector<Component *> m_Components;
};
