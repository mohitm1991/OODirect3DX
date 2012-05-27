#ifndef DIRECTX_TEXTURE2D
#define DIRECTX_TEXTURE2D

#include <D3D11.h>
#include <atlbase.h>
#include "Resource.h"

class Texture2D : public Resource
{
	friend class Resource;
	friend class ShaderResourceView;
	friend class SwapChain;

	private:
		CComPtr<ID3D11Texture2D> texture2D;
		D3D11_TEXTURE2D_DESC descriptor;

		Texture2D(const CComPtr<ID3D11Resource>& resource);
		Texture2D(const CComPtr<ID3D11Texture2D>& texture2D);
	public:
		virtual ~Texture2D();
		virtual Texture2D* convertToTexture2D();
		int getWidth();
		int getHeight();
		int getMipLevels();
		int getArraySize();
		DXGI_FORMAT getFormat();
		int getMultiSamplingCount();
		int getMultiSamplingQuality();
		D3D11_USAGE getUsage();
		int getBindFlags();
		int getCpuAccessFlags();
		int getMiscFlags();
};

#endif