#pragma once

#include <string>

class Sprite : public Component
{
 public:
	 Sprite(std::string _filename, std::string _name) : filename(_filename), name(_name) { type = "sprite"; }
  
  std::string filename;
  std::string name;
};

