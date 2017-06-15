#include "Timer.h"
#include "SDL2/SDL.h"

Timer::Timer()
{

}

Timer::~Timer()
{

}

void Timer::setup()
{
  NOW = SDL_GetPerformanceCounter();
  LAST = 0;
  delta = 0;

  timestamps.push_back(std::make_pair<const char*, double>("Timer Start", 0.0));
}

void Timer::profile(const char*  name)
{
  timestamps.push_back(std::make_pair<const char*, double>("", 0.0));
}

double Timer::getDelta()
{
  // Delta 
  LAST = NOW;
  NOW = SDL_GetPerformanceCounter();
  delta = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
  if (delta  > 1000.0)
    {
      // Artificially large delta, clamp back to 16
      delta = 16.0;
    }
  return delta;
}
