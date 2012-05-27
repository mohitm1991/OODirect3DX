#ifndef DIRECTX_SWAPCHAIN
#define DIRECTX_SWAPCHAIN

#include <D3D11.h>
#include <atlbase.h>
#include "SwapChainDescriptor.h"

class Resource;

class SwapChain
{
	// can change buffer count, size, format, refresh rate, windowed status without recreating
	friend class Device;

	private:
		CComPtr<IDXGISwapChain> swapChain;
		SwapChainDescriptor descriptor;

		SwapChain(const CComPtr<IDXGISwapChain>& swapChain, const SwapChainDescriptor& descriptor);
	public:
		const SwapChainDescriptor& getDescriptor();

		const Resource* getBackBuffer() const;
		void rotateChain() const;
};

#endif