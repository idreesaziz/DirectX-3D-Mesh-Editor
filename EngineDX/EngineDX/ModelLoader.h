#pragma once
#include "Mesh.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

class ModelLoader
{

private:
	const char* directory;
	void processNode(aiNode * node, const aiScene * scene);
	CMesh processMesh(aiMesh * mesh, const aiScene * scene);

public:
	bool LoadModel(std::string filename, std::vector<CMesh>* mStr);
	ModelLoader();
	~ModelLoader();
};

