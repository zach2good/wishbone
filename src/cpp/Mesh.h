#pragma once

#include <glad/glad.h>
#include <vector>
#include "glm/common.hpp"

class Mesh {

public:
    Mesh();
    virtual ~Mesh();

    void generateSpriteMesh(int width, int height,
        float pivotx, float pivoty,
        float uvwidth, float uvheight
    );

//private:
    GLuint m_nVertexBuffer;
    GLuint m_nUVBuffer;
    int m_nVertCount;

    void generateBuffers(std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& uv);
};