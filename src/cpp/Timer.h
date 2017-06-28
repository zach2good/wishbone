#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>

class Timer
{
public:
	static Timer& getInstance()
	{
		static Timer instance; 
		return instance;
	}

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

    std::vector<std::pair<std::string, double>>* current_timestamps;
	std::vector<std::pair<std::string, double>>* last_timestamps;
};
