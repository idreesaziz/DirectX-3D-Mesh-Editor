#include "pch.h"
#include "SkySphere.h"
#include "global.h"


CSkySphere::CSkySphere()
{
}


CSkySphere::CSkySphere(CRenderer& renderer, CCamera& camera)
	:
	pRenderer(&renderer),
	pCamera(&camera)
{
}

void CSkySphere::CreateSphere()
{
	CubeMesh Cube;
	Cube.CreateMesh();


	ID3D10Blob* VS = nullptr;
	ID3D10Blob* PS = nullptr;
	ID3D10Blob* ErrMSG = nullptr;

	D3DX11CompileFromFile("SkyShader.shader", 0, 0, "SKYMAP_VS", "vs_4_0", 0, 0, 0, &VS, &ErrMSG, 0);
	D3DX11CompileFromFile("SkyShader.shader", 0, 0, "SKYMAP_PS", "ps_4_0", 0, 0, 0, &PS, &ErrMSG, 0);

	// encapsulate both shaders into shader objects
	if (!ErrMSG && VS && PS)
	{
		pRenderer->GetDevice()->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), nullptr, &pVertexShader);
		pRenderer->GetDevice()->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), nullptr, &pPixelShader);
	}
	else
	{
		ELOG("The Shader file cannot be compiled. Please run this executable from the directory that contains the Shader file.");
		exit(1);
	}
	D3D11_INPUT_ELEMENT_DESC IED[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = ARRAYSIZE(IED);
	pRenderer->GetDevice()->CreateInputLayout(IED, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Buffers ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	HRESULT hr;
	//Creating a vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = Cube.GetVertices();

	hr = pRenderer->GetDevice()->CreateBuffer(&bd, &InitData, OUT &pVBuffer);	// creating vertex buffer

	//Creating an index buffer
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(short);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = Cube.GetIndices();

	hr = pRenderer->GetDevice()->CreateBuffer(&bd, &InitData, OUT &pIBuffer);  // creating index buffer

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Buffers ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void CSkySphere::InitilizeSky()
{
	CreateSphere();
}

void CSkySphere::RenderSky()
{
	const UINT vStride = sizeof(Vertex);
	const UINT vOffset = 0;
	pRenderer->GetDeviceContext()->VSSetShader(pVertexShader, 0, 0);
	pRenderer->GetDeviceContext()->PSSetShader(pPixelShader, 0, 0);
	pRenderer->GetDeviceContext()->IASetInputLayout(pLayout);
	pRenderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVBuffer, &vStride, &vOffset);
	pRenderer->GetDeviceContext()->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R16_UINT, 0);

	pRenderer->GetDeviceContext()->DrawIndexed(36, 0, 0);

}

CSkySphere::~CSkySphere()
{
}