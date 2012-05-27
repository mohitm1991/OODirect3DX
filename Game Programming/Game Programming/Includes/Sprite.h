#ifndef SPRITE_H_
#define SPRITE_H_

#include <D3D11.h>
#include <xnamath.h>

class Sprite
{
	private:
		XMFLOAT2 position;
		float rotationAngle;
		XMFLOAT2 scale;
	public:
		Sprite();
		virtual ~Sprite();

		XMMATRIX getWorldMatrix();

		void setPosition(int x, int y);
		void setPosition(XMFLOAT2& position);

		void setRotationAngle(float angle);
		
		void setScale(float x, float y);
		void setScale(XMFLOAT2& scale);
};

#endif