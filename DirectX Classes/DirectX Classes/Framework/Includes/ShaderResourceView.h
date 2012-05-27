#ifndef DIRECTX_SHADER_RESOURCE_VIEW
#define DIRECTX_SHADER_RESOURCE_VIEW

#include <D3D11.h>
#include <atlbase.h>

class Resource;

class ShaderResourceView
{
	friend class Device;
	friend class DeviceContext;

	private:
		CComPtr<ID3D11ShaderResourceView> view;

		ShaderResourceView(const CComPtr<ID3D11ShaderResourceView>& view);
	public:
		Resource* getResource();
};

#endif