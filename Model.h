#pragma once

#include "Utils.h"
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <vector>
#include "Texture.h"


class Model
{
public:
	Model(const std::string& pathToModel) : file(pathToModel) { }
	~Model();

	bool init();
	const std::vector<unsigned int>& getVAOs() { return vaos; }
	const std::vector<unsigned int>& getVBOs() { return vbos; }
	const std::vector<unsigned int>& getIBOs() { return ibos; }
	const std::vector<unsigned int>& getIndexCounts() { return indexCounts; }
	const std::vector<unsigned int>& getVertexCounts() { return vertexCounts; }
	const std::vector<Texture*>& getTextures() { return textures; }

private:
	std::string file;
	std::vector<unsigned int> vaos, vbos, ibos, indexCounts, vertexCounts;
	std::vector<Texture*> textures;
};