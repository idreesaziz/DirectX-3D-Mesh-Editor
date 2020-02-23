#include "pch.h"
#include "SolidShader.h"


bool CSolidShader::CreateCB1()
{
	if (!pConstatnBuffer[0])
	{
		HRESULT hr;
		// creating constant buffers
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(CB_SolidTick);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		hr = pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &pConstatnBuffer[0]);

		if (SUCCEEDED(hr)) return true;

	}
	return false;
}

bool CSolidShader::CreateCB2()
{
	if (!pConstatnBuffer[1])
	{
		HRESULT hr;
		// Cerating event based constant buffers
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(CB_SolidOnEvent);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		hr = pRenderer->GetDevice()->CreateBuffer(&bd, NULL, &pConstatnBuffer[1]);

		if (SUCCEEDED(hr)) return true;
	}
	return false;
}

void CSolidShader::UpdateCB1(const void* pData)
{
	if (pConstatnBuffer[0])
	{
		pRenderer->GetDeviceContext()->UpdateSubresource(pConstatnBuffer[0], 0, NULL, pData, 0, 0);
	}
}

void CSolidShader::UpdateCB2(const void * pData)
{
	if (pConstatnBuffer[1])
	{
		pRenderer->GetDeviceContext()->UpdateSubresource(pConstatnBuffer[1], 0, NULL, pData, 0, 0);
	}
}

ID3D11Buffer *& CSolidShader::GetCB1()
{
	return pConstatnBuffer[0];
}

ID3D11Buffer *& CSolidShader::GetCB2()
{
	return pConstatnBuffer[1];
}

CSolidShader::CSolidShader()
{
	pConstatnBuffer[0] = nullptr;
	pConstatnBuffer[1] = nullptr;
}
