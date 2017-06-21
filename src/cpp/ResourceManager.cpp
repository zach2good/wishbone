#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    // TODO: Preload everything here? Or in world?

    LoadShader("blank", "", "");

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

Shader* ResourceManager::LoadShader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    Shader* shader = new Shader(vertexPath, fragmentPath, geometryPath);
    m_mapShaders[name] = shader;
}

Texture* ResourceManager::LoadTexture(const char* name, const char* filename)
{
    Texture* tex = new Texture(filename);
    m_mapTextures[name] = tex;
}

Shader* ResourceManager::GetShader(const char* name)
{
    return m_mapShaders[name];
}

Texture* ResourceManager::GetTexture(const char* name)
{
    return m_mapTextures[name];
}


