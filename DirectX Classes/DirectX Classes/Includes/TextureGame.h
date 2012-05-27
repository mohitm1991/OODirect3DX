#ifndef TEXTUREGAME_H_
#define TEXTUREGAME_H_

#include "BaseGame.h"
#include <vector>
#include <xnamath.h>
using std::vector;

class TextureGame : public BaseGame
{
	private:
		class Vertex
		{
			private:
				XMFLOAT3 position;
				XMFLOAT2 textureCoordinate;
			public:
				Vertex();
				Vertex(const XMFLOAT3& position, const XMFLOAT2& textureCoordinate);

				void setPosition(const XMFLOAT3& position);
				XMFLOAT3 getPosition();

				void setCoordinate(const XMFLOAT2& textureCoordinate);
				XMFLOAT2 getCoordinate();
		};

		unique_ptr<VertexShader> vertexShader;
		unique_ptr<InputLayout> inputLayout;
		unique_ptr<PixelShader> pixelShader;
		unique_ptr<Buffer> vertexBuffer;
		unique_ptr<ShaderResourceView> srvTexture;
		unique_ptr<SamplerState> samplerState;
	public:
		TextureGame();
		virtual ~TextureGame();

		virtual bool loadContent();
		virtual void unloadContent();

		virtual void update(float deltaTime);
		virtual void render();
};

#endif