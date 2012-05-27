#include "Includes\SwapChain.h"
#include "Includes\Device.h"
#include "Includes\Resource.h"
#include <typeinfo>

SwapChain::SwapChain(const CComPtr<IDXGISwapChain>& chain, const SwapChainDescriptor& desc) : swapChain(chain), descriptor(desc)
{
}

const SwapChainDescriptor& SwapChain::getDescriptor()
{
	return descriptor;
}

const Resource* SwapChain::getBackBuffer() const
{
	if(swapChain == nullptr)
		return nullptr;

	CComPtr<ID3D11Resource> backBuffer(nullptr);
	swapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer));
	return new Resource(backBuffer);
}

void SwapChain::rotateChain() const
{
	if(swapChain != nullptr)
		swapChain->Present(0, 0);
}