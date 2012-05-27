#include "Includes\Sprite.h"
#include "Framework\Includes\Matrix.h"

Sprite::Sprite() : position(0.0f, 0.0f), rotationAngle(0.0f), scale(1.0f, 1.0f)
{
}

Matrix Sprite::getWorldMatrix()
{
	return Matrix::createScaling(scale.x, scale.y, 1.0f) * Matrix::createRotationZ(rotationAngle) * Matrix::createTranslation(position.x, position.y, 0.0f);
}

void Sprite::setPosition(int x, int y)
{
	position.x = static_cast<float>(x);
	position.y = static_cast<float>(y);
}

void Sprite::setRotationAngle(float angle)
{
	rotationAngle = angle;
}

void Sprite::setScale(float x, float y)
{
	scale.x = x;
	scale.y = y;
}