#ifndef SPRITEGAME_H_
#define SPRITEGAME_H_

#include "BaseGame.h"
#include <xnamath.h>
#include "Sprite.h"

class SpriteGame : public BaseGame
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

		CComPtr<ID3D11BlendState> blendState;
		Sprite sprites[2];
		XMMATRIX vpMatrix;
		CComPtr<ID3D11Buffer> mvpMatrixBuffer;

		CComPtr<ID3DBlob> compileShader(const char* fileName, const char* entryPoint, const char* shaderVersion);
	public:
		SpriteGame();
		virtual ~SpriteGame();

		virtual bool loadContent();
		virtual void unloadContent();

		virtual void update(float deltaTime);
		virtual void render();
};

#endif