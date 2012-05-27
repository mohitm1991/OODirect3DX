#ifndef DIRECTX_RESOURCE
#define DIRECTX_RESOURCE

#include <D3D11.h>
#include <atlbase.h>

class Texture2D;

class Resource
{
	friend class Device;
	friend class ShaderResourceView;
	friend class SwapChain;

	private:
		CComPtr<ID3D11Resource> resource;
	protected:
		Resource();
		Resource(const CComPtr<ID3D11Resource>& resource);
	public:
		virtual ~Resource();
		virtual Texture2D* convertToTexture2D();
};

#endif