#pragma once

#include <string>
#include <map>
#include <vector>
#include "tinyxml2.h"
using namespace tinyxml2;

struct MapLayer {
	std::string name;
	int width;
	int height;
	std::string encoding;
	std::string dataString;
	std::vector<int> data;
};

struct Map {
public:
	Map(std::string _filename);
	~Map();

//private:
	std::string filename;
	XMLDocument doc;
	std::string version;
	std::string tiledversion;
	std::string orientation;
	std::string renderOrder;
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int nextObjectId;
	std::map<std::string, MapLayer> layerMap;
};