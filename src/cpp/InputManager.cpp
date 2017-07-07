#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

bool InputManager::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
		return true;
	}

	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		if (event.key.repeat) return false;

		const bool isKeyDown = event.type == SDL_KEYDOWN;
		keyState[event.key.keysym.scancode] = isKeyDown;
		keyStateTimestamp[event.key.keysym.scancode] = SDL_GetTicks();
	}

	return false;
}

bool InputManager::isKeyDown(const SDL_Scancode code) const
{
	return keyState[code] > 0;
}

bool InputManager::isKeyUpdated(SDL_Scancode code, Uint32 timestamp) const
{
	return keyStateTimestamp[code] > timestamp;
}