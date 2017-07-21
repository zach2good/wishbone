#include "Mesh.h"

Mesh::Mesh(): 
    m_nVertexBuffer(0),
    m_nUVBuffer(0),
    m_nVertCount(0)
{
    // ===
}

Mesh::~Mesh()
{
    if (m_nVertexBuffer)
    {
        glDeleteBuffers(1, &m_nVertexBuffer);
        glDeleteBuffers(1, &m_nUVBuffer);
    }
}

void Mesh::generateSpriteMesh(int width, int height,
                                float pivotx, float pivoty,
                                float uvwidth, float uvheight)
{
    m_nVertCount = 6;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;

    // first triangle
    vertices.push_back(glm::vec3(-width * pivotx, -height * pivoty, 0.0f));
    vertices.push_back(glm::vec3(-width * pivotx, height - (height * pivoty), 0.0f));
    vertices.push_back(glm::vec3(width - (width * pivotx), height - (height * pivoty), 0.0f));

    // second triangle
    vertices.push_back(glm::vec3(width - (width * pivotx), height - (height * pivoty), 0.0f));
    vertices.push_back(glm::vec3(width - (width * pivotx), -height * pivoty, 0.0f));
    vertices.push_back(glm::vec3(-width * pivotx, -height * pivoty, 0.0f));

    // UV coordinates for each vertex.
    // uvs for first triangle
    uvs.push_back(glm::vec2(0.0f, uvheight));
    uvs.push_back(glm::vec2(0.0f, 0.0f));
    uvs.push_back(glm::vec2(uvwidth, 0.0f));

    // uvs for second triangle
    uvs.push_back(glm::vec2(uvwidth, 0.0f));
    uvs.push_back(glm::vec2(uvwidth, uvheight));
    uvs.push_back(glm::vec2(0.0f, uvheight));

    this->generateBuffers(vertices, uvs);
}

void Mesh::generateBuffers(std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& uv)
{
    //create GLuint _vertexbuffer;
    glGenBuffers(1, &m_nVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_nVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

    //create GLuint _uvbuffer;
    glGenBuffers(1, &m_nUVBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_nUVBuffer);
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
}