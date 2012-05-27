#ifndef TEXTUREGAME_H_
#define TEXTUREGAME_H_

#include "BaseGame.h"
#include <D3Dcompiler.h>
#include <xnamath.h>

class TextureGame : public BaseGame
{
	private:
		struct Vertex
		{
			XMFLOAT3 position;
			XMFLOAT2 texel;
		};

		CComPtr<ID3D11Buffer> vertexBuffer;
		CComPtr<ID3D11InputLayout> inputLayout;
		CComPtr<ID3D11VertexShader> vertexShader;
		CComPtr<ID3D11PixelShader> pixelShader;

		CComPtr<ID3D11ShaderResourceView> texture;
		CComPtr<ID3D11SamplerState> textureSampler;

		CComPtr<ID3DBlob> compileShader(const char* fileName, const char* entryPoint, const char* shaderVersion);
	public:
		TextureGame();
		virtual ~TextureGame();

		virtual bool loadContent();
		virtual void unloadContent();

		virtual void update(float deltaTime);
		virtual void render();
};

#endif