#include "Timer.h"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

Timer::Timer()
{
    // TODO: Use C++11 Pointers, I'm lazy and leaking a lot of memory, literally everywhere.
    
	current_timestamps = new std::vector<std::pair<std::string, double>>();
	last_timestamps = new std::vector<std::pair<std::string, double>>();
}

Timer::~Timer()
{
	// TODO: This was causing a crash? Hmmmmm
    //delete current_timestamps;
    //delete last_timestamps;
}

void Timer::setup()
{
    NOW = SDL_GetPerformanceCounter();
    LAST = 0;
    delta = 0;
}

void Timer::profile(const char*  name)
{
    current_timestamps->push_back(std::make_pair<std::string, double>(std::string(name), SDL_GetPerformanceCounter()));
}

void Timer::startFrame()
{
	current_timestamps->push_back(std::make_pair<std::string, double>(std::string("start frame"), SDL_GetPerformanceCounter()));
}

void Timer::endFrame()
{
	current_timestamps->push_back(std::make_pair<std::string, double>(std::string("end frame"), SDL_GetPerformanceCounter()));

	current_timestamps->clear();
}

double Timer::getDelta()
{
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    delta = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
    if (delta > 1000.0)
    {
        // Artificially large delta, clamp back to 16
        delta = 16.0;
    }
    return delta;
}

std::vector<std::pair<std::string, double>>* Timer::getStamps()
{
	return last_timestamps;
}
