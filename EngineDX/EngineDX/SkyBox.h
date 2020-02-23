#pragma once
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "SkyShader.h"

class CSkyBox
{
private:
	class CSkyShader* shader = nullptr;
	class CCamera* camera = nullptr;
	class CRenderer* renderer = nullptr;
	ID3D11ShaderResourceView* pTextureRV;
	ID3D11SamplerState* pSamplerLinear;
public:

	CSkyBox();
	void CreateSkyBox(class CRenderer* r, class CCamera* c);
	void Render();

	~CSkyBox();
};

