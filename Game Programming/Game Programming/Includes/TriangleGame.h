#ifndef TRIANGLEGAME_H_
#define TRIANGLEGAME_H_

#include "BaseGame.h"
#include <D3Dcompiler.h>
#include <xnamath.h>

class TriangleGame : public BaseGame
{
	private:
		struct Vertex
		{
			XMFLOAT3 position;
			XMFLOAT4 color;
		};

		CComPtr<ID3D11Buffer> vertexBuffer;
		CComPtr<ID3D11InputLayout> inputLayout;
		CComPtr<ID3D11VertexShader> vertexShader;
		CComPtr<ID3D11PixelShader> pixelShader;

		CComPtr<ID3DBlob> compileShader(const char* fileName, const char* entryPoint, const char* shaderVersion);
	public:
		TriangleGame();
		virtual ~TriangleGame();

		virtual bool loadContent();
		virtual void unloadContent();

		virtual void update(float deltaTime);
		virtual void render();
};

#endif