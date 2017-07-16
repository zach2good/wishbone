#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>

// TODO: rang and json throw a bunch of strange errors, whats the deal?

//https://github.com/agauniyal/rang
//#include "rang.hpp"

//https://github.com/nlohmann/json/tree/master
//#include "json.hpp"
//using json = nlohmann::json;

//http://glm.g-truc.net/0.9.8/index.html
#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "Timer.h"
#include "InputManager.h"
#include "Component.h"
#include "GameObject.h"
#include "World.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
//#include "ResourceManager.h"

// Memory leak detection in debug
#ifdef _DEBUG
#define _DEBUG_NEW_USE_ADDR2LINE 1
// This will redefine operator new!
#include "debug_new.h"
#endif
