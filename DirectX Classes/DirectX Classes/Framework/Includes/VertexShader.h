#ifndef DIRECTX_VERTEX_SHADER
#define DIRECTX_VERTEX_SHADER

#include <D3DX11.h>
#include <D3Dcompiler.h>
#include <atlbase.h>

class VertexShader
{
	friend class Device;
	friend class DeviceContext;

	private:
		CComPtr<ID3D11VertexShader> shader;
		CComPtr<ID3DBlob> compiledShaderData;

		VertexShader(const CComPtr<ID3D11VertexShader>& vertexShader, const CComPtr<ID3DBlob>& compiledShaderData);
};

#endif