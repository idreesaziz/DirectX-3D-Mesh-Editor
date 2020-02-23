#include "pch.h"
#include "CMesh.h"


void CMesh::CreateMesh()
{
}

void CMesh::CalculateNormals()
{
	// Vector cross product (B - A) with (C - A)
	// NormalX = ((by - ay) * (cz - az)) - ((cy - ay) * (bz - az));
	// NormalY = ((bz - az) * (cx - ax)) - ((cz - az) * (bx - ax));
	// NormalZ = ((bx - ax) * (cy - ay)) - ((cx - ax) * (by - ay));

	for (int i = 0; i < vIndices.size() -3 ; i += 3)
	{
		vVertices[vIndices[i]].NormalX     = ((vVertices[vIndices[i + 1]].y - vVertices[vIndices[i]].y) * (vVertices[vIndices[i + 2]].z - vVertices[vIndices[i]].z)) - ((vVertices[vIndices[i + 2]].y - vVertices[vIndices[i]].y) * (vVertices[vIndices[i + 1]].z - vVertices[vIndices[i]].z));
		vVertices[vIndices[i]].NormalY     = ((vVertices[vIndices[i + 1]].z - vVertices[vIndices[i]].z) * (vVertices[vIndices[i + 2]].x - vVertices[vIndices[i]].x)) - ((vVertices[vIndices[i + 2]].z - vVertices[vIndices[i]].z) * (vVertices[vIndices[i + 1]].x - vVertices[vIndices[i]].x));
		vVertices[vIndices[i]].NormalZ     = ((vVertices[vIndices[i + 1]].x - vVertices[vIndices[i]].x) * (vVertices[vIndices[i + 2]].y - vVertices[vIndices[i]].y)) - ((vVertices[vIndices[i + 2]].x - vVertices[vIndices[i]].x) * (vVertices[vIndices[i + 1]].y - vVertices[vIndices[i]].y));
		vVertices[vIndices[i + 1]].NormalX = ((vVertices[vIndices[i + 1]].y - vVertices[vIndices[i]].y) * (vVertices[vIndices[i + 2]].z - vVertices[vIndices[i]].z)) - ((vVertices[vIndices[i + 2]].y - vVertices[vIndices[i]].y) * (vVertices[vIndices[i + 1]].z - vVertices[vIndices[i]].z));
		vVertices[vIndices[i + 1]].NormalY = ((vVertices[vIndices[i + 1]].z - vVertices[vIndices[i]].z) * (vVertices[vIndices[i + 2]].x - vVertices[vIndices[i]].x)) - ((vVertices[vIndices[i + 2]].z - vVertices[vIndices[i]].z) * (vVertices[vIndices[i + 1]].x - vVertices[vIndices[i]].x));
		vVertices[vIndices[i + 1]].NormalZ = ((vVertices[vIndices[i + 1]].x - vVertices[vIndices[i]].x) * (vVertices[vIndices[i + 2]].y - vVertices[vIndices[i]].y)) - ((vVertices[vIndices[i + 2]].x - vVertices[vIndices[i]].x) * (vVertices[vIndices[i + 1]].y - vVertices[vIndices[i]].y));
		vVertices[vIndices[i + 2]].NormalX = ((vVertices[vIndices[i + 1]].y - vVertices[vIndices[i]].y) * (vVertices[vIndices[i + 2]].z - vVertices[vIndices[i]].z)) - ((vVertices[vIndices[i + 2]].y - vVertices[vIndices[i]].y) * (vVertices[vIndices[i + 1]].z - vVertices[vIndices[i]].z));
		vVertices[vIndices[i + 2]].NormalY = ((vVertices[vIndices[i + 1]].z - vVertices[vIndices[i]].z) * (vVertices[vIndices[i + 2]].x - vVertices[vIndices[i]].x)) - ((vVertices[vIndices[i + 2]].z - vVertices[vIndices[i]].z) * (vVertices[vIndices[i + 1]].x - vVertices[vIndices[i]].x));
		vVertices[vIndices[i + 2]].NormalZ = ((vVertices[vIndices[i + 1]].x - vVertices[vIndices[i]].x) * (vVertices[vIndices[i + 2]].y - vVertices[vIndices[i]].y)) - ((vVertices[vIndices[i + 2]].x - vVertices[vIndices[i]].x) * (vVertices[vIndices[i + 1]].y - vVertices[vIndices[i]].y));
	}
}

void CMesh::UpdateVertex(unsigned int index, Vertex * pVertex)
{
	vVertices[index] = *pVertex;
}

DirectX::XMMATRIX CMesh::GetGizmoMatrix()
{
	return GizmoMatrix * ModelMatrix;
}

Vertex * CMesh::GetVertices()
{
	return &vVertices[0];
}

short * CMesh::GetIndices()
{
	return &vIndices[0];
}

unsigned int CMesh::GetVerticesSize()
{
	return vVertices.size() * sizeof(Vertex);
}

unsigned int CMesh::GetIndicesSize()
{
	return vIndices.size() * sizeof(short);
}

unsigned int CMesh::GetVerticesCount()
{
	return vVertices.size();
}

unsigned int CMesh::GetIndicesCount()
{
	return vIndices.size();
}

const DirectX::XMMATRIX& CMesh::GetModelMatrix()
{
	return ModelMatrix;
}

void CMesh::SetModelMatrix(DirectX::XMMATRIX nModelMatrix)
{
	ModelMatrix = nModelMatrix;
}

CMesh::CMesh()
{
}

CMesh::CMesh(std::vector<Vertex>& pVertices, std::vector<short>& pIndices)
	:
	vVertices(pVertices),
	vIndices(pIndices)
{
	float x = 0;
	float y = 0;
	float z = 0;
	for (int i = 0; i < pVertices.size(); i++)
	{
		x += pVertices[i].x;
		y += pVertices[i].y;
		z += pVertices[i].z;
	}
	x /= pVertices.size();
	y /= pVertices.size();
	z /= pVertices.size();

	GizmoMatrix.r[0] = DirectX::XMVectorSet(1.f, 0.f, 0.f, 0.f);
	GizmoMatrix.r[1] = DirectX::XMVectorSet(0.f, 1.f, 0.f, 0.f);
	GizmoMatrix.r[2] = DirectX::XMVectorSet(0.f, 0.f, 1.f, 0.f);
	GizmoMatrix.r[3] = DirectX::XMVectorSet( x ,  y ,  z , 1.f);
}


CMesh::~CMesh()
{
}


