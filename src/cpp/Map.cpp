#include "Map.h"
#include <assert.h>

Map::Map(std::string _filename) {
	filename = _filename;

	// Load
	XMLError eResult = doc.LoadFile(filename.c_str());
	if (eResult != XML_SUCCESS) {
		assert("Problem loading XML");
	}

	// Basic Info
	auto map = doc.FirstChildElement("map");
	version = map->Attribute("version");
	tiledversion = map->Attribute("tiledversion");
	orientation = map->Attribute("orientation");
	renderOrder = map->Attribute("renderorder");

	width = std::stoi(map->Attribute("width"));
	height = std::stoi(map->Attribute("height"));
	tileWidth = std::stoi(map->Attribute("tilewidth"));
	tileHeight = std::stoi(map->Attribute("tileheight"));
	nextObjectId = std::stoi(map->Attribute("nextobjectid"));

	// Layers
	XMLElement* pLayerElement = map->FirstChildElement("layer");
	while (pLayerElement != nullptr) {
		MapLayer layer = MapLayer();
		layer.name = pLayerElement->Attribute("name");
		layer.width = std::stoi(pLayerElement->Attribute("width"));
		layer.height = std::stoi(pLayerElement->Attribute("height"));
		
		auto data = pLayerElement->FirstChildElement("data");
		layer.encoding = data->Attribute("encoding");

		layer.dataString = data->GetText();

		std::string buff;
		for (int i = 0; i < layer.dataString.size(); i++)
		{		
			if (layer.dataString[i] != ' ' && 
				layer.dataString[i] != ',' && 
				layer.dataString[i] != '\n') 
			{
				buff += layer.dataString[i];
			} 
			else if (!buff.empty()) 
			{
				layer.data.push_back(std::stoi(buff));
				buff = "";
			}
		}
		layerMap[layer.name] = layer;

		// Next Layer
		pLayerElement = pLayerElement->NextSiblingElement("layer");
	}
}