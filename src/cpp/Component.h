#pragma once

#include <string>

class GameObject;

class Component
{
public:
    // TODO: Break out into enum, stirng comparisons are pricey
    std::string type;

    // All Components must know about their parent objects
    GameObject* parent;

    /*

      template <T>
      T* FindObjectOfTypeInParentGO<T>

      Example: The player component is going to want access to the AnimatedSprite and Physics components of its parent GO
      Return nullptr on fail
     */
protected:

private:

};
