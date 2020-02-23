#pragma once
#include "Global.h"
#include "Renderer.h"

// this class uses a CRenderer object-pointer to compile the vertex and pixel shader
// also, uses CRenderer::GetDeviceContext() and CRenderer::GetDevice()...
// initialize the CRenderer-pointer(pRenderer) before calling any other functions
// to compile the shaders using your CRenderer object.


// these constant buffer data structures are based on the shader constant buffers
// in the shader file. TickConstantBuffer updates every frame,
// while OvEvent is updated eventually, (on events like window_resize)


// CSolidShader inherits from Cshader with added functionality to fit the default solid shader model
// CWireframeShader also inherits from Cshader with added functionality for the wireframe shader model

//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------

class CShader
{
protected:
	class CRenderer			*pRenderer				= nullptr;
	ID3D11VertexShader		*pVertexShader			= nullptr;
	ID3D11GeometryShader	*pGeometryShader		= nullptr;
	ID3D11PixelShader		*pPixelShader			= nullptr;
	ID3D11InputLayout		*pLayout				= nullptr;
	ID3D11Buffer			*pVBuffer				= nullptr;
	ID3D11Buffer			*pIBuffer				= nullptr;


public:
	CShader();
	void SetRendererObject(CRenderer* pRenderer);

	bool CreateShaderObject(const char* filePath,
							const char* pVertexFunctionName,
							const char* pGeometryFunctionName,
							const char* pPixelFunctionName);

	bool CreateVertexBuffers(Vertex* pVertices,
						   unsigned int verticesSize);

	bool CreateIndexBuffers (short*   pIndices, 
						   unsigned int  indicesSize);

	void UpdateVertex(void * pData, size_t size);

	//Getters
	ID3D11Buffer*&			GetVertexBuffer();
	ID3D11Buffer*&			GetIndexBuffer();
	ID3D11VertexShader*&	GetVertexShader();
	ID3D11GeometryShader*&	GetGeometryShader();
	ID3D11PixelShader*&		GetPixelShader();
	ID3D11InputLayout*		GetLayout();

	~CShader();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CB_WireframeTick
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
};

struct CB_WireframeOnEvent
{
	DirectX::XMMATRIX mProjection;
};

class CWireframeShader : public CShader
{
private:
	ID3D11Buffer		*pConstantBuffer[2];

public:
	bool CreateCB1();
	bool CreateCB2();

	void UpdateCB1(const void* pData);
	void UpdateCB2(const void* pData);

	ID3D11Buffer*& GetCB1();
	ID3D11Buffer*& GetCB2();

	CWireframeShader();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CB_VertexTick
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
};

struct CB_VertexOnEvent
{
	DirectX::XMMATRIX mProjection;
};


class CVertexOverlayShader : public CShader
{

private:
	ID3D11Buffer			*pConstantBuffer[2];

public:
	bool CreateCB1();
	bool CreateCB2();
	void UpdateCB1(const void* pData);
	void UpdateCB2(const void* pData);

public:
	//Getters
	ID3D11Buffer*& GetCB1();
	ID3D11Buffer*& GetCB2();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CB_SolidTick
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMFLOAT4 vLightDirection;
	DirectX::XMFLOAT4 vLightColor;
};

struct CB_SolidOnEvent
{
	DirectX::XMMATRIX mProjection;
	DirectX::XMFLOAT3A AmbientDown;
	DirectX::XMFLOAT3A AmbientRange;
};

class CSolidShader : public CShader
{

private:
	ID3D11Buffer		*pConstatnBuffer[2];

public:
	bool CreateCB1();
	bool CreateCB2();

	void UpdateCB1(const void* pData);
	void UpdateCB2(const void* pData);

	//Getters
	ID3D11Buffer*& GetCB1();
	ID3D11Buffer*& GetCB2();

	CSolidShader();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CB_SkyTick
{
	DirectX::XMMATRIX mView;
};

struct CB_SkyOnEvent
{
	DirectX::XMMATRIX mProjection;
};

class CSkyShader : public CShader
{
private:
	ID3D11Buffer		*pConstantBuffer[2];

public:
	bool CreateTickCB();
	bool CreateOnEventCB();

	void UpdateCB1(const void* pData);
	void UpdateCB2(const void* pData);

	ID3D11Buffer*& GetCB1();
	ID3D11Buffer*& GetCB2();

	CSkyShader();
};