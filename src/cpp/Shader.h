#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "common.h"

// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h

class Shader
{
public:
    unsigned int ID;

    Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath = std::string());
    ~Shader();

    // TODO: Make everything chainable like this
    Shader& Use();

	Shader& SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	Shader& SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	Shader& SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	Shader& SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	Shader& SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	Shader& SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	Shader& SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	Shader& SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	Shader& SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};
