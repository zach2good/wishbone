#pragma once

#include <string>
#include <map>

// SDL
#include "Shader.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include "Sprite.h"

// TiledMap

class ResourceManager
{
public:

    // static
    ResourceManager();
    ~ResourceManager();

    // TODO: Upgrade to use std::string?
    Shader* LoadShader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    // TODO: const
    Texture* LoadTexture(const char* name, const char* filename);

    // Make SpriteSheets and Sprites public?

    // TiledMap* LoadTiledMap(std::string name, std:;string filename)
    // Music* LoadMusic(std::string name, std::string filename)
    // Sound* LoadSound(std::string name, std::string filename)
    // JSON* LoadJSON(std::string name, std::string filename)

    Shader* GetShader(const char* name);
    Texture* GetTexture(const char* name);

    // TiledMap* GetTiledMap(std::string name)
    // Music* GetMusic(std::string name)
    // Sound* GetSound(std::string name)
    // JSON* GetJSON(std::string name)

    // bool SaveTiledMap(std::string name)
    // bool SaveJSON(std::string name)

    // Debug UI
    // Produce manifest of memory usage/allocation and buffer content where possible
    // ImGui will only be called from the Renderer, so this information has to be
    // passed in a sane format 

private:

    std::map<const char*, Shader*> m_mapShaders;
    std::map<const char*, Texture*> m_mapTextures;
    std::map<const char*, SpriteSheet*> m_mapSpriteSheets;
    std::map<const char*, Sprite*> m_mapSprites;

    // std::map<std::string, TiledMap*> m_TiledMaps;
    // std::map<std::string, Music*> m_Music;
    // std::map<std::string, Sound*> m_Sounds;
    // std::map<std:;string, JSON*> m_JSON;
};
