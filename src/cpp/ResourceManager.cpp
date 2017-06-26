#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    LoadShader("sprite", "res/shaders/sprite.vs", "res/shaders/sprite.fs");

    auto player_texture = LoadTexture("player", "res/graphics/player.png");
    LoadSprite("player", player_texture);
    LoadSpriteSheet("player2", player_texture, 0, 0);
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

Sprite* ResourceManager::LoadSprite(std::string name, Texture* tex)
{
    Sprite* sp = new Sprite(tex);
    m_mapSprites[name] = sp;
    return sp;
}

SpriteSheet* ResourceManager::LoadSpriteSheet(std::string name, Texture* tex, int x, int y)
{
    SpriteSheet* ss = new SpriteSheet(tex, x, y);
    m_mapSpriteSheets[name] = ss;
    return ss;
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

Sprite* ResourceManager::GetSprite(std::string name)
{
    assert(m_mapSprites[name]);
    return m_mapSprites[name];
}

SpriteSheet* ResourceManager::GetSpriteSheet(std::string name)
{
    assert(m_mapSpriteSheets[name]);
    return m_mapSpriteSheets[name];
}

