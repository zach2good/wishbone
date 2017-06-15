#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

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
