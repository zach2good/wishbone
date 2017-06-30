#include "InputManager.h"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

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
            if (event.key.keysym.sym == SDLK_d)
            {
            }
        }
    }

    // If quit requested
    return quit;
}

//TODO: Create input queue or state to pass into World (and possibly renderer for options)
