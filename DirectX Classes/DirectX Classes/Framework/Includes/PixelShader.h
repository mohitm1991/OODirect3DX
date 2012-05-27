#ifndef DIRECTX_PIXEL_SHADER
#define DIRECTX_PIXEL_SHADER

#include <D3D11.h>
#include <atlbase.h>

class PixelShader
{
	friend class Device;
	friend class DeviceContext;

	private:
		CComPtr<ID3D11PixelShader> shader;

		PixelShader(const CComPtr<ID3D11PixelShader>& shader);
};

#endif