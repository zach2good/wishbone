#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <array>

#include "Singleton.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool handleEvent(const SDL_Event& event);

	bool isKeyDown(SDL_Scancode code) const;
	bool isKeyUpdated(SDL_Scancode code, Uint32 timestamp) const;

	// Keys
	std::array<bool, SDL_NUM_SCANCODES> keyState = std::array<bool, SDL_NUM_SCANCODES>{ {false} };
	std::array<Uint32, SDL_NUM_SCANCODES> keyStateTimestamp = std::array<Uint32, SDL_NUM_SCANCODES> { {0} };
};

typedef Singleton<InputManager> InputManagerSingleton; 
