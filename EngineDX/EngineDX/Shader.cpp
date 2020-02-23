#include "pch.h"
#include "Shader.h"

CShader::CShader(){}

void CShader::SetRendererObject(CRenderer * pRenderer)
{
	this->pRenderer = pRenderer;
}

//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
bool CShader::CreateShaderObject(const char * filePath,
								const char * pVertexFunctionName,
								const char * pGeometryFunctionName,
								const char * pPixelFunctionName)
{
	ID3D10Blob* VS     = nullptr;
	ID3D10Blob* GS	   = nullptr;
	ID3D10Blob* PS     = nullptr;
	ID3D10Blob* ErrMSG = nullptr;

	D3DX11CompileFromFile(filePath, 0, 0, pVertexFunctionName, "vs_4_0", 0, 0, 0, &VS, &ErrMSG, 0);
	D3DX11CompileFromFile(filePath, 0, 0, pGeometryFunctionName, "gs_4_0", 0, 0, 0, &GS, &ErrMSG, 0);
	D3DX11CompileFromFile(filePath, 0, 0, pPixelFunctionName,  "ps_4_0", 0, 0, 0, &PS, &ErrMSG, 0);

	// encapsulate both shaders into shader objects
	if (!ErrMSG && VS && PS && GS )
	{
		pRenderer->GetDevice()->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), nullptr, &pVertexShader);
		pRenderer->GetDevice()->CreateGeometryShader(GS->GetBufferPointer(), GS->GetBufferSize(), nullptr, &pGeometryShader);
		pRenderer->GetDevice()->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), nullptr, &pPixelShader);
	}
	else
	{
		ELOG("The Shader file cannot be compiled. Please run this executable from the directory that contains the Shader file.");
		exit(1);
		return false;
	}
	D3D11_INPUT_ELEMENT_DESC IED[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE( IED );
	pRenderer->GetDevice()->CreateInputLayout(IED, numElements, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	return true;
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

bool CShader::CreateVertexBuffers(Vertex* pVertices, unsigned int verticesSize)
{
	if (!pVBuffer)
	{
		HRESULT hr;
		//Creating a vertex buffer
		D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = verticesSize;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		D3D11_SUBRESOURCE_DATA InitData;
			ZeroMemory(&InitData, sizeof(InitData));
			InitData.pSysMem = pVertices;

		hr = pRenderer->GetDevice()->CreateBuffer(&bd, &InitData, OUT &pVBuffer);	// creating the buffer

		if (SUCCEEDED(hr)) return true;
	}
	return false;
}
bool CShader::CreateIndexBuffers(short * pIndices, unsigned int indicesSize)
{
	if (!pIBuffer)
	{
		HRESULT hr;
		//Creating an index buffer
		D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = indicesSize;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA InitData;
			ZeroMemory(&InitData, sizeof(InitData));
			InitData.pSysMem = pIndices;

		hr = pRenderer->GetDevice()->CreateBuffer(&bd, &InitData, &pIBuffer);
		
		if (SUCCEEDED(hr)) return true;
	}
	return false;
}

void CShader::UpdateVertex(void* pData, size_t size)
{
	HRESULT hr;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//  Disable GPU access to the vertex buffer data.
	hr = pRenderer->GetDeviceContext()->Map(pVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//  Update the vertex buffer here.
	memcpy(mappedResource.pData, pData, size);

	//  Reenable GPU access to the vertex buffer data.
	pRenderer->GetDeviceContext()->Unmap(pVBuffer, 0);
}

ID3D11Buffer *& CShader::GetVertexBuffer()
{
	return pVBuffer;
}

ID3D11Buffer *& CShader::GetIndexBuffer()
{
	return pIBuffer;
}

ID3D11VertexShader *& CShader::GetVertexShader()
{
	return pVertexShader;
}

ID3D11GeometryShader *& CShader::GetGeometryShader()
{
	return pGeometryShader;
}

ID3D11PixelShader *& CShader::GetPixelShader()
{
	return pPixelShader;
}

ID3D11InputLayout * CShader::GetLayout()
{
	return pLayout;
}


CShader::~CShader()
{
}
