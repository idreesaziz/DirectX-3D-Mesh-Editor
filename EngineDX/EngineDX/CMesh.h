#pragma once
#include "Global.h"
#include <assimp\Importer.hpp>

enum class E_EDIT_MODE
{
	M_FALSE = -1,
	M_SELECTED = 0,
	M_VERTEX = 1,
};

class CMesh
{

private:
	DirectX::XMMATRIX ModelMatrix = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX GizmoMatrix = DirectX::XMMatrixIdentity();

protected:
	std::vector<Vertex> vVertices;
	std::vector<short> vIndices;


public:
	Vertex* GetVertices();
	short* GetIndices();
	unsigned int GetVerticesSize();
	unsigned int GetIndicesSize();
	unsigned int GetVerticesCount();
	unsigned int GetIndicesCount();
	virtual void CreateMesh();
	const DirectX::XMMATRIX& GetModelMatrix();
	void SetModelMatrix(DirectX::XMMATRIX nModelMatrix);
	void CalculateNormals();
	void UpdateVertex(unsigned int index, Vertex * pVertex);
	DirectX::XMMATRIX GetGizmoMatrix();
	CMesh();
	CMesh(std::vector<Vertex>& pVertices, std::vector<short>& pIndices);
	~CMesh();
};

// Cube Class
class CubeMesh : public CMesh
{

private:


public:
	void CreateMesh() override;
	~CubeMesh();

};