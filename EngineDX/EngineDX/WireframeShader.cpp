#include "pch.h"
#include "WireframeShader.h"


bool CWireframeShader::CreateCB1()
{
	if (!pConstantBuffer[0])
	{
		HRESULT hr;
		// creating constant buffers
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(CB_WireframeTick);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		hr = pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &pConstantBuffer[0]);

		if (SUCCEEDED(hr)) return true;

	}
	return false;
}

bool CWireframeShader::CreateCB2()
{
	if (!pConstantBuffer[1])
	{
		HRESULT hr;
		// Cerating event based constant buffers
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(CB_WireframeOnEvent);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		hr = pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &pConstantBuffer[1]);

		if (SUCCEEDED(hr)) return true;
	}
	return false;
}

void CWireframeShader::UpdateCB1(const void* pData)
{
	if (pConstantBuffer[0])
	{
		pRenderer->GetDeviceContext()->UpdateSubresource(pConstantBuffer[0], 0, NULL, pData, 0, 0);
	}
}

void CWireframeShader::UpdateCB2(const void * pData)
{
	if (pConstantBuffer[1])
	{
		pRenderer->GetDeviceContext()->UpdateSubresource(pConstantBuffer[1], 0, NULL, pData, 0, 0);
	}
}

ID3D11Buffer *& CWireframeShader::GetCB1()
{
	return pConstantBuffer[0];
}

ID3D11Buffer *& CWireframeShader::GetCB2()
{
	return pConstantBuffer[1];
}

CWireframeShader::CWireframeShader()
{
	pConstantBuffer[0] = nullptr;
	pConstantBuffer[1] = nullptr;
}

