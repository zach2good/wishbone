#pragma once

#include <string>
#include <map>

// SDL
#include "Shader.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include "Sprite.h"

class ResourceManager
{
public:
    
    ResourceManager();
    ~ResourceManager();

    Shader* LoadShader(std::string name, std::string vertexPath, std::string fragmentPath, std::string geometryPath = std::string());

    // TODO: const
    Texture* LoadTexture(std::string name, std::string filename);

    Sprite* LoadSprite(std::string name, Texture* tex);
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

    // TiledMap* GetTiledMap(std::string name)
    // Music* GetMusic(std::string name)
    // Sound* GetSound(std::string name)
    // JSON* GetJSON(std::string name)

    // bool SaveTiledMap(std::string name)
    // bool SaveJSON(std::string name)

    // Debug UI
    // Produce manifest of memory usage/allocation and buffer content where possible
    // ImGui will only be called from the Renderer, so this information has to
    // be
    // passed in a sane format

    // private:

    std::map<std::string, Shader*> m_mapShaders;
    std::map<std::string, Texture*> m_mapTextures;
    std::map<std::string, SpriteSheet*> m_mapSpriteSheets;
    std::map<std::string, Sprite*> m_mapSprites;

    // std::map<std::string, TiledMap*> m_TiledMaps;
    // std::map<std::string, Music*> m_Music;
    // std::map<std::string, Sound*> m_Sounds;
    // std::map<std:;string, JSON*> m_JSON;
};
