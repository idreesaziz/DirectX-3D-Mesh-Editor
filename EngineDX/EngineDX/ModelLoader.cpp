#include "pch.h"
#include "ModelLoader.h"
#include "Global.h"

static std::vector<CMesh>* meshes = nullptr;
bool ModelLoader::LoadModel(std::string filename, std::vector<CMesh>* mStr)
{
	Assimp::Importer importer;
	meshes = mStr;
	const aiScene* pScene = importer.ReadFile(filename,
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded|
		aiProcess_JoinIdenticalVertices);

	if (pScene == NULL)
		return false;

	this->directory = filename.substr(0, filename.find_last_of('/')).c_str();

	processNode(pScene->mRootNode, pScene);

	return true;
}

void ModelLoader::processNode(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes->push_back(this->processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

CMesh ModelLoader::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<short> indices;
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;
		if (mesh->mNormals)
		{
			vertex.NormalX = mesh->mNormals->x;
			vertex.NormalY = mesh->mNormals->y;
			vertex.NormalZ = mesh->mNormals->z;
		}
		if (mesh->mNumUVComponents)
		{
			vertex.u = mesh->mNumUVComponents[0];
			vertex.v = mesh->mNumUVComponents[1];
		}
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		
		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	
	CMesh ret = CMesh(vertices, indices);
	ret.CalculateNormals();
	return ret;
}

ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}
