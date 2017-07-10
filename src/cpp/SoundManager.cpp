#include "SoundManager.h"

SoundManager::SoundManager()
{
	isInit = false;
}

SoundManager::~SoundManager()
{
	for (auto& sound : loadedSounds)
	{
		delete sound.second;
	}
}

void SoundManager::Init()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "!SDL_INIT_AUDIO" << std::endl;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "!Mix_OpenAudio" << std::endl;
	}

	Load("res/sounds/jump.wav", "jump");
	Load("res/sounds/laser.wav", "laser");
	Load("res/sounds/pickup.wav", "pickup");
}

void SoundManager::Load(std::string path, std::string name)
{
	loadedSounds[name] = new Sound(path);
	while (Mix_PlayingMusic());
}

void SoundManager::Play(std::string name)
{
	Mix_PlayChannel(-1, loadedSounds[name]->wave, 0);
}