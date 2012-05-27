#include "Includes\ViewPort.h"

ViewPort::ViewPort() : viewPort()
{
}

void ViewPort::setSize(int width, int height)
{
	viewPort.Width = static_cast<float>(width);
	viewPort.Height = static_cast<float>(height);
}

int ViewPort::getWidth()
{
	return static_cast<int>(viewPort.Width);
}

int ViewPort::getHeight()
{
	return static_cast<int>(viewPort.Height);
}

void ViewPort::setDepth(float minDepth, float maxDepth)
{
	viewPort.MinDepth = minDepth;
	viewPort.MaxDepth = maxDepth;
}

float ViewPort::getMinDepth()
{
	return viewPort.MinDepth;
}

float ViewPort::getMaxDepth()
{
	return viewPort.MaxDepth;
}

void ViewPort::setOrigin(int topLeftX, int topLeftY)
{
	viewPort.TopLeftX = static_cast<float>(topLeftX);
	viewPort.TopLeftY = static_cast<float>(topLeftY);
}

int ViewPort::getOriginX()
{
	return static_cast<int>(viewPort.TopLeftX);
}

int ViewPort::getOriginY()
{
	return static_cast<int>(viewPort.TopLeftY);
}