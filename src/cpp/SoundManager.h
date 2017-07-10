#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <unordered_map>
#include <string>
#include <iostream>

struct Sound {
	Sound(std::string path) {	
	}
	~Sound() {
	}
};

class SoundManager{

	static SoundManager& Instance()
	{
		static SoundManager myInstance;
		return myInstance;
	}
	// delete copy and move constructors and assign operators
	SoundManager(SoundManager const&) = delete;             // Copy construct
	SoundManager(SoundManager&&) = delete;                  // Move construct
	SoundManager& operator=(SoundManager const&) = delete;  // Copy assign
	SoundManager& operator=(SoundManager &&) = delete;      // Move assign

	SoundManager();
	~SoundManager();

	void Load(std::string path, std::string name);
	void Play(std::string name);

	std::unordered_map<std::string, Sound*> loadedSounds;
};