#ifndef TRIANGLEGAME_H_
#define TRIANGLEGAME_H_

#include "BaseGame.h"
#include <vector>
#include <xnamath.h>
using std::vector;

class TriangleGame : public BaseGame
{
	private:
		class Vertex
		{
			private:
				XMFLOAT3 position;
				XMFLOAT4 color;
			public:
				Vertex();
				Vertex(const XMFLOAT3& position, const XMFLOAT4& color);

				void setPosition(const XMFLOAT3& position);
				XMFLOAT3 getPosition();

				void setColor(const XMFLOAT4& color);
				XMFLOAT4 getColor();
		};

		unique_ptr<VertexShader> vertexShader;
		unique_ptr<InputLayout> inputLayout;
		unique_ptr<PixelShader> pixelShader;
		unique_ptr<Buffer> vertexBuffer;
	public:
		TriangleGame();
		virtual ~TriangleGame();

		virtual bool loadContent();
		virtual void unloadContent();

		virtual void update(float deltaTime);
		virtual void render();
};

#endif