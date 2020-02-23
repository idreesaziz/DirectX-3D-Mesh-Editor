#include "Renderer.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
namespace HLRA
{


	struct sBuffer
	{

	};
	class cRenderer
	{
	private:
		IDXGISwapChain			*SwapChain = nullptr;
		ID3D11Device			*Device	= nullptr;
		ID3D11DeviceContext		*DeviceContext = nullptr;

	public:
		ID3D11Device*		 GetDevice();
		ID3D11DeviceContext* GetDeviceContext();

		void CreateDeviceInstance(void* OutWin)
		{
			DXGI_SWAP_CHAIN_DESC scd;
			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
				scd.BufferCount			= 1;
				scd.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
				scd.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
				scd.OutputWindow		= *(HWND*)OutWin;
				scd.SampleDesc.Count	= 1;
				scd.Windowed			= TRUE;

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
		}

		~cRenderer()
		{
			SwapChain->Release();
			Device->Release();
			DeviceContext->Release();
		}
	};
	class cShader 
	{

	};
}