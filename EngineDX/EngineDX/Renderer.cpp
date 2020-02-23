#include "pch.h"
#include "Renderer.h"


CRenderer::CRenderer()
{
}

void CRenderer::InitializeRenderer(HWND& hWnd, unsigned int bufHeight, unsigned bufWidth) // TODO: take a RECT-pointer and use the abstracted cDevice to render
{
	if (!SwapChain && !Device && !DeviceContext && !backbuffer)
	{
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
			scd.BufferCount = 1;                                    // one back buffer
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			scd.OutputWindow = hWnd;                                // the window to be used
			scd.SampleDesc.Count = 1;                               // how many 'multi-samples'
			scd.Windowed = TRUE;                                    // windowed/full-screen mode
		
		D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&scd,
			&SwapChain,
			&Device,
			NULL,
			&DeviceContext);
		//..

		ID3D11Texture2D *pBackBuffer;
		SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
		Device->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
		pBackBuffer->Release();

		// creating the depth stencil
		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory(&descDepth, sizeof(descDepth));
			descDepth.Width = bufWidth;
			descDepth.Height = bufHeight;
			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			descDepth.SampleDesc.Count = 1;
			descDepth.SampleDesc.Quality = 0;
			descDepth.Usage = D3D11_USAGE_DEFAULT;
			descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;
			Device->CreateTexture2D(&descDepth, NULL, &DepthStencil);

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
			descDSV.Format = descDepth.Format;
			descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;
			Device->CreateDepthStencilView(DepthStencil, &descDSV, &DepthStencilView);

		// Create rasterizer state
		D3D11_RASTERIZER_DESC rasterizerStateDesc;
		ZeroMemory(&rasterizerStateDesc, sizeof(rasterizerStateDesc));
			rasterizerStateDesc.FillMode = D3D11_FILL_SOLID;
			rasterizerStateDesc.CullMode = D3D11_CULL_NONE;
			rasterizerStateDesc.FrontCounterClockwise = true;
			rasterizerStateDesc.DepthClipEnable = true;
		Device->CreateRasterizerState(&rasterizerStateDesc, &RasterizerState);

		DeviceContext->OMSetRenderTargets(1, &backbuffer, DepthStencilView);

		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
			viewport.TopLeftX	= 0;
			viewport.TopLeftY	= 0;
			viewport.Width		= bufWidth;
			viewport.Height		= bufHeight;
			viewport.MinDepth	= 0.0f;
			viewport.MaxDepth	= 1.0f;

		DeviceContext->RSSetViewports(1, &viewport);

	}
}

void CRenderer::UseShader(CShader * shader, UINT vStride, UINT vOffset, D3D_PRIMITIVE_TOPOLOGY PrimitiveMode)
{ 
	CurrentShader = shader;
	auto pVBuffer = shader->GetVertexBuffer();
	auto pIBuffer = shader->GetIndexBuffer();
	if (DeviceContext)
	{
		DeviceContext->VSSetShader(shader->GetVertexShader(), 0, 0);
		DeviceContext->GSSetShader(shader->GetGeometryShader(), 0, 0);
		DeviceContext->PSSetShader(shader->GetPixelShader(), 0, 0);
		DeviceContext->IASetInputLayout(shader->GetLayout());
		DeviceContext->IASetVertexBuffers(0, 1, &pVBuffer, &vStride, &vOffset);
		DeviceContext->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R16_UINT, 0);
		DeviceContext->IASetPrimitiveTopology(PrimitiveMode);
	}
}

void CRenderer::RenderFrame(void(*r)(void), float R, float G, float B, float A)
{
	const float BackColor[4] = { R, G, B, A };
	DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	DeviceContext->ClearRenderTargetView(backbuffer, BackColor);

	r();

	SwapChain->Present(0, 0);
}

void CRenderer::BindConstatntBuffer(int startSlot, int numBuffers, ID3D11Buffer *const *ppConstantBuffers)
{
	DeviceContext->VSSetConstantBuffers(startSlot, numBuffers, ppConstantBuffers);
	DeviceContext->GSSetConstantBuffers(startSlot, numBuffers, ppConstantBuffers);
	DeviceContext->PSSetConstantBuffers(startSlot, numBuffers, ppConstantBuffers);
}

CRenderer::~CRenderer()
{
	if (SwapChain)SwapChain->Release();
	if (backbuffer)backbuffer->Release();
	if (Device)Device->Release();
	if (DeviceContext)DeviceContext->Release();
}


// Getters
IDXGISwapChain * CRenderer::GetSwapChain()			{	return SwapChain;		}
ID3D11Device * CRenderer::GetDevice()				{	return Device;			}
ID3D11DeviceContext * CRenderer::GetDeviceContext()	{	return DeviceContext;	}
ID3D11RenderTargetView * CRenderer::GetBackbuffer()	{	return backbuffer;		}

ID3D11RasterizerState * CRenderer::GetRasterizerState()
{
	return RasterizerState;
}

//CSolidShader * CRenderer::GetCurrentShader()
//{
//	return CurrentShader;
//}
