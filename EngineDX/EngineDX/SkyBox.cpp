#include "pch.h"
#include "SkyBox.h"


CSkyBox::CSkyBox()
{
}

void CSkyBox::CreateSkyBox(class CRenderer* r, class CCamera* c)
{
	camera = c;
	renderer = r;
	Vertex verts[8]
	{
		{-200.0, -200.0,  200.0, 0.0f, 0.0f, 0.0f, -1.0, -1.0,  1.0},
		{ 200.0, -200.0,  200.0, 0.0f, 0.0f, 0.0f,  1.0, -1.0,  1.0},
		{ 200.0,  200.0,  200.0, 0.0f, 0.0f, 0.0f,  1.0,  1.0,  1.0},
		{-200.0,  200.0,  200.0, 0.0f, 0.0f, 0.0f, -1.0,  1.0,  1.0},
		// back
		{-200.0, -200.0, -200.0, 0.0f, 0.0f, 0.0f, -1.0, -1.0, -1.0},
		{ 200.0, -200.0, -200.0, 0.0f, 0.0f, 0.0f,  1.0, -1.0, -1.0},
		{ 200.0,  200.0, -200.0, 0.0f, 0.0f, 0.0f,  1.0,  1.0, -1.0},
		{-200.0,  200.0, -200.0, 0.0f, 0.0f, 0.0f, -1.0,  1.0, -1.0}
	};

	WORD indices[36]
	{

		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3

	};

	shader = new CSkyShader[sizeof(CSkyShader)];

	shader->SetRendererObject(r);																	// Binding renderer object to the shader
	shader->CreateShaderObject("SkyShader.shader", "SKYMAP_VS", "SKYMAP_GS" ,"SKYMAP_PS");
	shader->CreateVertexBuffers(verts, sizeof(Vertex) * 8);											// Creating vertex buffers...
	shader->CreateIndexBuffers((short*)indices, sizeof(short) * 36);									// Creating index buffers...
	shader->CreateTickCB();																			// Creating constant buffers...
	shader->CreateOnEventCB();																		// Creating constant buffers...

	// loading the cubemap
	D3DX11_IMAGE_LOAD_INFO loadSMInfo;
	loadSMInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	ID3D11Texture2D* SMTexture = 0;
	D3DX11CreateTextureFromFile(renderer->GetDevice(), "SkyTextureCubemap.dds", &loadSMInfo, 0, (ID3D11Resource**)&SMTexture, 0);
	D3D11_TEXTURE2D_DESC SMTextureDesc;
	SMTexture->GetDesc(&SMTextureDesc);
	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = SMTextureDesc.Format;
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;
	renderer->GetDevice()->CreateShaderResourceView(SMTexture, &SMViewDesc, &pTextureRV);


	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	renderer->GetDevice()->CreateSamplerState(&sampDesc, &pSamplerLinear);
}

void CSkyBox::Render()
{

	auto pVBuffer = shader->GetVertexBuffer();
	auto pIBuffer = shader->GetIndexBuffer();
	UINT vStride = sizeof(Vertex);
	UINT vOffset = 0;
	renderer->GetDeviceContext()->VSSetShader(shader->GetVertexShader(), 0, 0);
	renderer->GetDeviceContext()->PSSetShader(shader->GetPixelShader(), 0, 0);
	renderer->GetDeviceContext()->IASetInputLayout(shader->GetLayout());
	renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVBuffer, &vStride, &vOffset);
	renderer->GetDeviceContext()->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R16_UINT, 0);
	
	renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	renderer->GetDeviceContext()->VSSetConstantBuffers(0, 1, &shader->GetCB1());
	renderer->GetDeviceContext()->PSSetConstantBuffers(0, 1, &shader->GetCB1());
	//renderer->GetDeviceContext()->VSSetConstantBuffers(1, 1, &shader->GetCB2());
	//renderer->GetDeviceContext()->PSSetConstantBuffers(1, 1, &shader->GetCB2());
	renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureRV);
	renderer->GetDeviceContext()->PSSetSamplers(0, 1, &pSamplerLinear);

	CB_SkyTick cb;
	cb.mView = XMMatrixTranspose(camera->GetViewMatrix());
	shader->UpdateCB1(&cb);

	CB_SkyOnEvent ecb;
	ecb.mProjection = camera->GetProjectionMatrix();
	shader->UpdateCB2(&cb);

	renderer->GetDeviceContext()->DrawIndexed(36, 0, 0);

}

CSkyBox::~CSkyBox()
{
	if (shader) delete[] shader;
}
