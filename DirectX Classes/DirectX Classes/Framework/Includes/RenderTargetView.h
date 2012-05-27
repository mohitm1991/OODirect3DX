#ifndef DIRECTX_RENDER_TARGET_VIEW
#define DIRECTX_RENDER_TARGET_VIEW

#include <D3D11.h>
#include <atlbase.h>

class RenderTargetView
{
	friend class Device;
	friend class DeviceContext;

	private:
		CComPtr<ID3D11RenderTargetView> view;

		RenderTargetView(const CComPtr<ID3D11RenderTargetView>& view);
};

#endif