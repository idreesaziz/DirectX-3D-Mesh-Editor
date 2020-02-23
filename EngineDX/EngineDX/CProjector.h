#pragma once
#include "CMesh.h"
#include "CCamera.h"
#include "Global.h"
#include "Shader.h"
struct SProjectedMesh
{
	std::vector<DirectX::XMVECTOR> verts;
};
class Projector
{
private:
	std::vector<SProjectedMesh>* vMeshes = nullptr;

	bool ProjectionDevicedOnce = false;

public:
	bool vertsUpdated = false;
	Projector();
	void ProjectVerts(CMesh* pMesh,
				 size_t Size,
				 const DirectX::XMMATRIX* mView,
				 const DirectX::XMMATRIX* mProj,
				 std::vector<SProjectedMesh>& projectedVectors);

	bool TraceRay(POINT mouse);
	bool InsideTri(float ax,
					  float ay,
					  float bx,
					  float by,
					  float cx,
					  float cy,
					  float mouseX,
					  float mouseY);

	VOID CALLBACK LineDDAProc(
		_In_ int    X,
		_In_ int    Y,
		_In_ LPARAM lpData
	);

	~Projector();
};

