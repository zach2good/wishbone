#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <array>

#define gInput InputManager::Instance()

class InputManager
{
public:
	static InputManager& Instance()
	{
		static InputManager myInstance;
		return myInstance;
	}

	// delete copy and move constructors and assign operators
	InputManager(InputManager const&) = delete;             // Copy construct
	InputManager(InputManager&&) = delete;                  // Move construct
	InputManager& operator=(InputManager const&) = delete;  // Copy assign
	InputManager& operator=(InputManager &&) = delete;      // Move assign

	InputManager();
	~InputManager();

	bool handleEvent(const SDL_Event& event);

	bool isKeyDown(SDL_Scancode code) const;
	bool isKeyUpdated(SDL_Scancode code, Uint32 timestamp) const;

	// Keys
	std::array<bool, SDL_NUM_SCANCODES> keyState = std::array<bool, SDL_NUM_SCANCODES>{ {false} };
	std::array<Uint32, SDL_NUM_SCANCODES> keyStateTimestamp = std::array<Uint32, SDL_NUM_SCANCODES> { {0} };
};
