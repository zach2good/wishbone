#pragma once

#include <string>

class GameObject;

class Component
{
public:
    // TODO: Break out into enum, stirng comparisons are pricey
    std::string type;
    GameObject* parent;

protected:

private:

};
