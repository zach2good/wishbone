#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>

#define gTimer Timer::Instance()

class Timer
{
public:
	static Timer& Instance()
	{
		static Timer myInstance;
		return myInstance;
	}

	// delete copy and move constructors and assign operators
	Timer(Timer const&) = delete;             // Copy construct
	Timer(Timer&&) = delete;                  // Move construct
	Timer& operator=(Timer const&) = delete;  // Copy assign
	Timer& operator=(Timer &&) = delete;      // Move assign

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

    std::shared_ptr<std::vector<std::pair<std::string, double>>> current_timestamps;
	std::shared_ptr<std::vector<std::pair<std::string, double>>> last_timestamps;
};