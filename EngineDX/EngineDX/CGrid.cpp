#include "pch.h"
#include "CGrid.h"


void CGrid::CreateGrid(int columns, int rows, int x, int y, CRenderer& renderer, CCamera& camera)
{
	currentRenderer = &renderer;
	pCamera = &camera;

	float a = (x / 2) * -1;
	float b = (y / 2);

	for (int i = 0; i <= columns; i++)
	{
		Vertices.push_back(Vertex(a + ((x/columns) * i), 0.0f, b));
		Vertices.push_back(Vertex(a + ((x/columns) * i), 0.0f, b - y));
	}

	for (int i = 0; i <= rows; i++)
	{
		Vertices.push_back(Vertex(a	   , 0.0f, b - ((y / rows) * i)));
		Vertices.push_back(Vertex(a + x, 0.0f, b - ((y / rows) * i)));
	}

	std::vector<short> indices;

	for (int i = 0; i < Vertices.size(); i++)
		indices.push_back(i);

	shader = new CWireframeShader[sizeof(CWireframeShader)];

	shader->SetRendererObject(&renderer);
	shader->CreateShaderObject("GridShader.shader", "WIREFRAME_VS", "WIREFRAME_GS", "WIREFRAME_PS");
	shader->CreateVertexBuffers(&Vertices[0], Vertices.size() * sizeof(Vertex));
	shader->CreateIndexBuffers(&indices[0], indices.size() * sizeof(short));
	shader->CreateCB1();
	shader->CreateCB2();
}

void CGrid::DrawGrid()
{
	CB_WireframeTick cb;
	cb.mWorld = XMMatrixTranspose(DirectX::XMMatrixIdentity());
	cb.mView = XMMatrixTranspose(pCamera->GetViewMatrix());
	shader->UpdateCB1(&cb);

	CB_WireframeOnEvent ecb;
	ecb.mProjection = XMMatrixTranspose(pCamera->GetProjectionMatrix());
	shader->UpdateCB2(&ecb);

	auto pVBuffer = shader->GetVertexBuffer();
	auto pIBuffer = shader->GetIndexBuffer();
	UINT vStride = sizeof(Vertex);
	UINT vOffset = 0; 
	currentRenderer->GetDeviceContext()->VSSetShader(shader->GetVertexShader(), 0, 0);
	currentRenderer->GetDeviceContext()->GSSetShader(shader->GetGeometryShader(), 0, 0);
	currentRenderer->GetDeviceContext()->PSSetShader(shader->GetPixelShader(), 0, 0);
	currentRenderer->GetDeviceContext()->IASetInputLayout(shader->GetLayout());
	currentRenderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVBuffer, &vStride, &vOffset);
	currentRenderer->GetDeviceContext()->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R16_UINT, 0);

	currentRenderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	currentRenderer->GetDeviceContext()->VSSetConstantBuffers(0, 1, &shader->GetCB1());
	currentRenderer->GetDeviceContext()->PSSetConstantBuffers(0, 1, &shader->GetCB1());

	currentRenderer->GetDeviceContext()->VSSetConstantBuffers(1, 1, &shader->GetCB2());
	currentRenderer->GetDeviceContext()->PSSetConstantBuffers(1, 1, &shader->GetCB2());
	
	currentRenderer->GetDeviceContext()->DrawIndexed(Vertices.size(), 0, 0);
}

CWireframeShader* CGrid::GetShader()
{
	return shader;
}

CGrid::CGrid()
{
}


CGrid::~CGrid()
{
	delete[] shader;
}
