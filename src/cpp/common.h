#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>

//https://github.com/agauniyal/rang
#include "rang.hpp"

//https://github.com/nlohmann/json/tree/master
#include "json.hpp"
using json = nlohmann::json;

//http://glm.g-truc.net/0.9.8/index.html
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
