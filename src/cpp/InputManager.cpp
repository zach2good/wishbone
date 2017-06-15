#include "InputManager.h"

#include "SDL2/SDL.h"

bool InputManager::poll()
{
  bool quit = false;
  SDL_Event event;		 
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      {
	quit = true;
	break;
      }
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
	{
	  quit = true;
	}
      
      // TODO: Replace with InputManager and add a PlayerController Component
      // InputManager singleton
      // Command Pattern
      // Record/Replay input and game state
      // Dump to .dmp file on crash, on exception or assert?
      if (event.key.keysym.sym == SDLK_d)
	{
	  //go.x += 10;
	}	  
    }
  }
  
  // If quit requested
  return quit;
}

//TODO: Create input queue or state to pass into World (and possibly renderer for options)
