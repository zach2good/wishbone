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
#include "Mesh.h"
#include "Map.h"

class ResourceManager
{
public:
    
    ResourceManager();
    ~ResourceManager();

    Shader* LoadShader(std::string name, std::string vertexPath, std::string fragmentPath, std::string geometryPath = std::string());
    Texture* LoadTexture(std::string name, std::string filename);
    Mesh* LoadMesh(std::string name, int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight);
	Map* LoadMap(std::string name, std::string filename);

    Shader* GetShader(std::string name);
    Texture* GetTexture(std::string name);
    Mesh* GetMesh(std::string name);
    Map* GetMap(std::string name);

    //private:
    std::map<std::string, Shader*> m_mapShaders;
    std::map<std::string, Texture*> m_mapTextures;
    std::map<std::string, Mesh*> m_mapMeshes; 
    std::map<std::string, Map*> m_mapMaps;
};
