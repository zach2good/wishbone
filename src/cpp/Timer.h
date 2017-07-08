#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include "Singleton.h"

class Timer
{
public:
    Timer();
    ~Timer();

    void setup();
    void profile(const char* name);
    double getDelta();

	void startFrame();
	void endFrame();
	std::vector<std::pair<std::string, double>>* getStamps();

    double NOW;
    double LAST;
    double delta;
	float multiplier = 1;

    std::vector<std::pair<std::string, double>>* current_timestamps;
	std::vector<std::pair<std::string, double>>* last_timestamps;
};

typedef Singleton<Timer> TimerSingleton;