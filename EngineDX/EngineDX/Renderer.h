#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include "Global.h"
#include "Shader.h"
#include "Mesh.h"
#include "SkyBox.h"
#include "Grid.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

struct CDevice 
{
	ID3D11Device			*pDevice					= nullptr;
	ID3D11DeviceContext		*pDeviceContext				= nullptr;
	IDXGISwapChain			*pSwapChain					= nullptr;
	ID3D11RenderTargetView	*pbackbuffer				= nullptr;
	ID3D11DepthStencilView	*DepthStencilView			= nullptr;
	void CreateDevice();
	void CreateDepthStencil();
	void CreateViewport(RECT rc);
};

class CRenderer
{
private:
	IDXGISwapChain				*SwapChain				= nullptr;
	ID3D11Device				*Device					= nullptr;
	ID3D11DeviceContext			*DeviceContext			= nullptr;
	ID3D11RenderTargetView		*backbuffer				= nullptr;
	ID3D11Texture2D				*DepthStencil			= nullptr;
	ID3D11DepthStencilView		*DepthStencilView		= nullptr;
	ID3D11RasterizerState		*RasterizerState		= nullptr;
	class CShader				*CurrentShader		= nullptr;
	std::thread					 SceneThread;

public:
	CRenderer();
	void InitializeRenderer(HWND& hWnd, unsigned int bufHeight, unsigned bufWidth);
	void UseShader(CShader* shader, UINT vStride, UINT vOffset, D3D_PRIMITIVE_TOPOLOGY PrimitiveMode);
	void RenderFrame(void(*r)(void), float R, float G, float B, float A);
	void BindConstatntBuffer(int startSlot, int numBuffers, ID3D11Buffer *const *ppConstantBuffers);

	~CRenderer();

	// Getters
	IDXGISwapChain*			GetSwapChain();
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetDeviceContext();
	ID3D11RenderTargetView* GetBackbuffer();
	ID3D11RasterizerState*	GetRasterizerState();
	CShader*				GetCurrentShader();
};

