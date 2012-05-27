#ifndef SPRITE_H_
#define SPRITE_H_

#include <D3D11.h>
#include <xnamath.h>

class Matrix;

class Sprite
{
	private:
		XMFLOAT2 position;
		float	 rotationAngle;
		XMFLOAT2 scale;
	public:
		Sprite();

		Matrix getWorldMatrix();

		void setPosition(int x, int y);
		void setRotationAngle(float angle);
		void setScale(float x, float y);
};

#endif