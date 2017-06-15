#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>

class Timer
{
 public:
  Timer();
  ~Timer();
  
  void setup();
  void profile(const char* name);
  double getDelta();
  
 private:
  double NOW;
  double LAST;
  double delta;

  std::vector<std::pair<const char*, double>> timestamps;
};
