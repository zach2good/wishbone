#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    LoadShader("sprite", "res/shaders/sprite.vs", "res/shaders/sprite.fs");

    LoadTexture("player", "res/graphics/player.png");
}

ResourceManager::~ResourceManager()
{
    for (auto& shader : m_mapShaders)
    {
        // Destroy Shader
    }

    for (auto& tex : m_mapTextures)
    {
        // Destroy Texture
    }
}

Shader* ResourceManager::LoadShader(std::string name, std::string vertexPath, std::string fragmentPath, std::string geometryPath)
{
    Shader* shader = new Shader(vertexPath, fragmentPath, geometryPath);
    m_mapShaders[name] = shader;
    return shader;
}

Texture* ResourceManager::LoadTexture(std::string name, std::string filename)
{
    Texture* tex = new Texture(filename);
    m_mapTextures[name] = tex;
    return tex;
}

Shader* ResourceManager::GetShader(std::string name)
{
    assert(m_mapShaders[name]);
    return m_mapShaders[name];
}

Texture* ResourceManager::GetTexture(std::string name)
{
    return m_mapTextures[name];
}


