#pragma once


#include "SDL2/SDL.h"

class InputManager
{
 public:
  InputManager& instance();
  
  bool poll();
  
 private:
  // Static instance pointer
  
  // Key up state
  // key down state
  // Mouse state

  // Controller state
};
