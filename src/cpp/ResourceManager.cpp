#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    // ===
}

ResourceManager::~ResourceManager()
{
    for (auto shader : m_mapShaders)
    {
		delete shader.second;
    }

    for (auto tex : m_mapTextures)
    {
		delete tex.second;
    }

    for (auto mesh : m_mapMeshes)
    {
        delete mesh.second;
    }

    for (auto map : m_mapMaps)
    {
        delete map.second;
    }
}

Shader* ResourceManager::LoadShader(std::string name, std::string vertexPath, std::string fragmentPath, std::string geometryPath)
{
    if (m_mapShaders[name]) {
        return m_mapShaders[name];
    }

    Shader* shader = new Shader(vertexPath, fragmentPath, geometryPath);
    m_mapShaders[name] = shader;
    return shader;
}

Texture* ResourceManager::LoadTexture(std::string name, std::string filename)
{
    if (m_mapTextures[name]) {
        return m_mapTextures[name];
    }

    Texture* tex = new Texture(filename);
    m_mapTextures[name] = tex;
    return tex;
}

Mesh* ResourceManager::LoadMesh(std::string name, int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight)
{
    if (m_mapMeshes[name]) {
        return m_mapMeshes[name];
    }

    Mesh* mesh = new Mesh();
    mesh->generateSpriteMesh(width, height, pivotx, pivoty, uvwidth, uvheight);
    m_mapMeshes[name] = mesh;
    return mesh;
}

Map* ResourceManager::LoadMap(std::string name, std::string filename)
{
    if (m_mapMaps[name]) {
        return m_mapMaps[name];
    }

    Map* map = new Map(filename);
    m_mapMaps[name] = map;
    return map;
}

Shader* ResourceManager::GetShader(std::string name)
{
    assert(m_mapShaders[name]);
    return m_mapShaders[name];
}

Texture* ResourceManager::GetTexture(std::string name)
{
    assert(m_mapTextures[name]);
    return m_mapTextures[name];
}

Mesh* ResourceManager::GetMesh(std::string name)
{
    assert(m_mapMeshes[name]);
    return m_mapMeshes[name];
}

Map* ResourceManager::GetMap(std::string name)
{
    assert(m_mapMaps[name]);
    return m_mapMaps[name];
}