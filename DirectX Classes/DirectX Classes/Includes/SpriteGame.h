#ifndef SPRITEGAME_H_
#define SPRITEGAME_H_

#include "BaseGame.h"
#include "Sprite.h"
#include <vector>
#include <xnamath.h>
using std::vector;

class SpriteGame : public BaseGame
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
		unique_ptr<ShaderResourceView> srvTexture;
		unique_ptr<SamplerState> samplerState;
		unique_ptr<Buffer> vertexBuffer;
		unique_ptr<Buffer> matrixBuffer;
		unique_ptr<BlendState> blendState;
		Matrix viewProjectionMatrix;
		Sprite sprites[3];
		float angleStep;
		float scaleStep;
		float angleFactor;
	public:
		SpriteGame();
		virtual ~SpriteGame();

		virtual bool loadContent();
		virtual void unloadContent();

		virtual void update(float deltaTime);
		virtual void render();
};

#endif