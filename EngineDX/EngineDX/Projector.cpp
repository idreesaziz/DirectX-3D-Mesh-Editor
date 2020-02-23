#include "pch.h"
#include "Projector.h"

Projector::Projector()
{
}

void Projector::ProjectVerts(CMesh * pMesh, size_t Size, const DirectX::XMMATRIX* mView, const DirectX::XMMATRIX* mProj, std::vector<SProjectedMesh>& projectedVectors)
{
	if (!vertsUpdated)
	{
		vMeshes = &projectedVectors;
		using namespace DirectX;
		if (ProjectionDevicedOnce)
		{
			for (int i = 0; i < Size / sizeof(CMesh); i++)
			{
				for (int j = 0; j < pMesh[i].GetVerticesCount(); j++)
				{

					DirectX::XMVECTOR v1;
					v1.m128_f32[0] = pMesh[i].GetVertices()[j].x;
					v1.m128_f32[1] = pMesh[i].GetVertices()[j].y;
					v1.m128_f32[2] = pMesh[i].GetVertices()[j].z;
					v1.m128_f32[3] = 1.f;


					v1 = XMVector4Transform(XMVector4Transform(XMVector4Transform(v1, pMesh[i].GetModelMatrix()), *mView), *mProj);


					v1.m128_f32[0] /= v1.m128_f32[2];
					v1.m128_f32[1] /= v1.m128_f32[2];
					v1.m128_f32[2] /= v1.m128_f32[2];

					projectedVectors[i].verts[j] = v1;

				}
			}
			vertsUpdated = true;
		}
		else
		{
			for (int i = 0; i < Size / sizeof(CMesh); i++)
			{
				for (int j = 0; j < pMesh[i].GetVerticesCount(); j++)
				{

					DirectX::XMVECTOR v1;
					v1.m128_f32[0] = pMesh[i].GetVertices()[j].x;
					v1.m128_f32[1] = pMesh[i].GetVertices()[j].y;
					v1.m128_f32[2] = pMesh[i].GetVertices()[j].z;
					v1.m128_f32[3] = 1.f;


					projectedVectors[i].verts.emplace_back(XMVECTOR());
					v1 = XMVector4Transform(XMVector4Transform(XMVector4Transform(v1, pMesh[i].GetModelMatrix()), *mView), *mProj);


					v1.m128_f32[0] /= v1.m128_f32[2];
					v1.m128_f32[1] /= v1.m128_f32[2];
					v1.m128_f32[2] /= v1.m128_f32[2];

					projectedVectors[i].verts[j] = v1;

				}
			}
			ProjectionDevicedOnce = true;
			vertsUpdated = true;
		}
	}
}

bool Projector::TraceRay(POINT mouse)
{
	
	return 0;
}

bool Projector::InsideTri(float ax,
	float ay,
	float bx,
	float by, 
	float cx, 
	float cy, 
	float mouseX, 
	float mouseY)
{
	float errorMargin = 0.000001;
	float A = abs((ax*(by - cy)) + (bx*(cy - ay)) + (cx*(ay - by)));
	float a1 = abs((mouseX*(by - cy)) + (bx*(cy - mouseY)) + (cx*(mouseY - by)));
	float a2 = abs((ax*(mouseY - cy)) + (mouseX*(cy - ay)) + (cx*(ay - mouseY)));
	float a3 = abs((ax*(by - mouseY)) + (bx*(mouseY - ay)) + (mouseX*(ay - by)));

	if (A >= (a1 + a2 + a3 - errorMargin))
		return true;
	return false;
}

Projector::~Projector()
{
}
