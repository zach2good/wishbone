#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    LoadShader("sprite", "res/shaders/sprite.vs", "res/shaders/sprite.fs");

    auto player_texture = LoadTexture("player", "res/graphics/player.png");
	auto enemies_texture = LoadTexture("enemies", "res/graphics/enemies.png");
	auto tiles_texture = LoadTexture("tiles", "res/graphics/tiles.png");
	auto portrait_texture = LoadTexture("portrait", "res/graphics/portrait.png");

	auto player_spritesheet = LoadSpriteSheet("player_spritesheet", player_texture, 4, 2);
	auto enemies_spritesheet = LoadSpriteSheet("enemies_spritesheet", enemies_texture, 4, 3);
	auto tiles_spritesheet = LoadSpriteSheet("tiles_spritesheet", tiles_texture, 8, 6);

	LoadSprite("player1", player_spritesheet, 0, 0);
	LoadSprite("player2", player_spritesheet, 1, 0);
	LoadSprite("player3", player_spritesheet, 2, 0);
	LoadSprite("player4", player_spritesheet, 3, 0);
	LoadSprite("player5", player_spritesheet, 0, 1);
	LoadSprite("player6", player_spritesheet, 1, 1);
	LoadSprite("player7", player_spritesheet, 2, 1);
	LoadSprite("player8", player_spritesheet, 3, 1);

	LoadSprite("eye1", enemies_spritesheet, 0, 2);
	LoadSprite("eye2", enemies_spritesheet, 1, 2);
	LoadSprite("eye3", enemies_spritesheet, 2, 2);

	LoadSprite("tile1", tiles_spritesheet, 0, 0);

	// TODO: Generate pools of GameObjects and Components
    for (int i = 0; i < 500; i++) {
        m_vGameObjects.push_back(new GameObject(""));
    }

    // TODO: What needs pooling?
    // Create 100 of each kind of component? They're just data classes so they're essentially free
    // (*as long as they're cleaned up correctly)
    // -> Log warnings when components start getting reused, or expand the vector holding them and log warnings then

    // Create loads of physics objects and make them inactive, when they're needed change their state and set them to active
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

	for (auto ss : m_mapSpriteSheets)
	{
		delete ss.second;
	}

	for (auto sp : m_mapSprites)
	{
		delete sp.second;
	}

    for(auto go : m_vGameObjects)
    {
        delete go;
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
    // TODO: Can you assert with a warning message? When these trigger its not immediatley clear why
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

GameObject* ResourceManager::GetGameObject(std::string name)
{
    // Index = GameObjectMap.size() (Remember size and capacity are different)
    // if there isn't a GameObject at map[name], 
    // claim a GO from the premade vector (perfect use of shared_ptr
    // Remove from vector and insert into map?    
    
    return nullptr;
}

