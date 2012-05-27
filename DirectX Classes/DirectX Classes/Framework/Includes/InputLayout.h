#ifndef DIRECTX_INPUT_LAYOUT
#define DIRECTX_INPUT_LAYOUT

#include <D3D11.h>
#include <atlbase.h>

class InputLayout
{
	friend class Device;
	friend class DeviceContext;

	private:
		CComPtr<ID3D11InputLayout> layout;

		InputLayout(const CComPtr<ID3D11InputLayout>& layout);
};

#endif