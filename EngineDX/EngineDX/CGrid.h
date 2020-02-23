#pragma once
#include "Global.h"
#include "Shader.h"
#include "WireframeShader.h"
#include "CRenderer.h"
#include "CCamera.h"

class CGrid
{
private:
	std::vector<Vertex> Vertices;
	class CRenderer* currentRenderer;
	class CWireframeShader* shader;
	class CCamera* pCamera;

public:
	void CreateGrid(int columns, int rows, int x, int y, class CRenderer& renderer, CCamera& camera);
	void DrawGrid();
	class CWireframeShader* GetShader();
	CGrid();
	~CGrid();
};