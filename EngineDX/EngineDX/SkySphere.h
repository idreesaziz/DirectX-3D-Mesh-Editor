#pragma once
#include "CCamera.h"
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"

struct SWorldView
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
};

class CSkySphere
{

private:
	void CreateSphere();
	ID3D11VertexShader	*pVertexShader	= nullptr;
	ID3D11PixelShader	*pPixelShader	= nullptr;
	ID3D11Buffer		*pMatCB			= nullptr;
	ID3D11InputLayout	*pLayout		= nullptr;
	ID3D11Buffer		*pVBuffer		= nullptr;
	ID3D11Buffer		*pIBuffer		= nullptr;
	class CRenderer		*pRenderer		= nullptr;
	class CCamera		*pCamera		= nullptr;

public:
	void InitilizeSky();
	void RenderSky();
	CSkySphere();
	CSkySphere(CRenderer& renderer, CCamera& camera);
	~CSkySphere();
};

