#include "SoundManager.h"

SoundManager::SoundManager()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "!SDL_INIT_AUDIO" << std::endl;
	}

	Load("res/sounds/jump.wav", "jump");
	Load("res/sounds/laser.wav", "laser");
	Load("res/sounds/pickup.wav", "pickup");
}

SoundManager::~SoundManager()
{
	
}

void SoundManager::Load(std::string path, std::string name)
{
	
}

void SoundManager::Play(std::string name)
{
	//loadedSounds[name];
}