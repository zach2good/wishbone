#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <unordered_map>
#include <string>
#include <iostream>

#include "Singleton.h"

struct Sound {
	Sound(std::string path) {	
	}
	~Sound() {
	}
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void Load(std::string path, std::string name);
	void Play(std::string name);

	std::unordered_map<std::string, Sound*> loadedSounds;
};

typedef Singleton<SoundManager> SoundManagerSingleton;
