#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "Shader.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Map.h"

class ResourceManager
{
public:
    
    ResourceManager();
    ~ResourceManager();

    Shader* LoadShader(std::string name, std::string vertexPath, std::string fragmentPath, std::string geometryPath = std::string());
    Texture* LoadTexture(std::string name, std::string filename);
    Sprite* LoadSprite(std::string name, Texture* tex);
	Sprite* LoadSprite(std::string name, SpriteSheet* ss, int x, int y);
    SpriteSheet* LoadSpriteSheet(std::string name, Texture* tex, int x, int y);

    // Make SpriteSheets and Sprites public?

    // TiledMap* LoadTiledMap(std::string name, std:;string filename)
    // Music* LoadMusic(std::string name, std::string filename)
    // Sound* LoadSound(std::string name, std::string filename)
    // JSON* LoadJSON(std::string name, std::string filename)

    Shader* GetShader(std::string name);
    Texture* GetTexture(std::string name);
    Sprite* GetSprite(std::string name);
    SpriteSheet* GetSpriteSheet(std::string name);
    GameObject* GetGameObject(std::string name);
                              
    // TiledMap* GetTiledMap(std::string name)
    // Music* GetMusic(std::string name)
    // Sound* GetSound(std::string name)
    // JSON* GetJSON(std::string name)

    // bool SaveTiledMap(std::string name)
    // bool SaveJSON(std::string name)

    //private:
    std::map<std::string, Shader*> m_mapShaders;
    std::map<std::string, Texture*> m_mapTextures;
    std::map<std::string, SpriteSheet*> m_mapSpriteSheets;
    std::map<std::string, Sprite*> m_mapSprites;

    std::vector<GameObject*> m_vGameObjects;
    std::vector<Component*> m_vComponents;
    
	std::unique_ptr<Map> map;

    // std::map<std::string, TiledMap*> m_TiledMaps;
    // std::map<std::string, Music*> m_Music;
    // std::map<std::string, Sound*> m_Sounds;
    // std::map<std:;string, JSON*> m_JSON;

	//TODO: Keep track of GOs and Comps?
};
