#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    LoadShader("sprite", "res/shaders/sprite.vs", "res/shaders/sprite.fs");

    auto player_texture = LoadTexture("player", "res/graphics/player.png");
	auto enemies_texture = LoadTexture("enemies", "res/graphics/enemies.png");
	auto tiles_texture = LoadTexture("enemies", "res/graphics/tiles.png");

	auto player_spritesheet = LoadSpriteSheet("player_spritesheet", player_texture, 4, 2);
	auto enemies_spritesheet = LoadSpriteSheet("enemies_spritesheet", enemies_texture, 4, 3);
	auto tiles_spritesheet = LoadSpriteSheet("tiles_spritesheet", tiles_texture, 8, 6);

	LoadSprite("player1", player_spritesheet, 0, 0);
	LoadSprite("player2", player_spritesheet, 1, 0);
	LoadSprite("player3", player_spritesheet, 2, 0);
	LoadSprite("player4", player_spritesheet, 3, 0);
	LoadSprite("player5", player_spritesheet, 0, 1);
	LoadSprite("player6", player_spritesheet, 1, 1);

	LoadSprite("eye1", enemies_spritesheet, 0, 2);
	LoadSprite("eye2", enemies_spritesheet, 1, 2);
	LoadSprite("eye3", enemies_spritesheet, 2, 2);
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

Sprite* ResourceManager::LoadSprite(std::string name, SpriteSheet* ss, int x, int y)
{
	Sprite* sp = new Sprite(ss, x, y);
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
    // TODO: Replace these asserts with a runtime warning and load the resource anyway
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

