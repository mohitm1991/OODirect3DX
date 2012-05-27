#include "Includes\Sprite.h"

Sprite::Sprite() : position(0, 0), rotationAngle(0.0f), scale(1.0f, 1.0f)
{
}

Sprite::~Sprite()
{
}

XMMATRIX Sprite::getWorldMatrix()
{
	return XMMatrixTranslation(position.x, position.y, 0.0f) * XMMatrixRotationZ(rotationAngle) * XMMatrixScaling(scale.x, scale.y, 1.0f);
}

void Sprite::setPosition(int x, int y)
{
	position.x = static_cast<float>(x);
	position.y = static_cast<float>(y);
}

void Sprite::setPosition(XMFLOAT2& position)
{
	this->position = position;
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

void Sprite::setScale(XMFLOAT2& scale)
{
	this->scale = scale;
}