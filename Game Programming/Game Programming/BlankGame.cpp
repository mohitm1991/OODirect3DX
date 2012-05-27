#include "Includes\BlankGame.h"

BlankGame::BlankGame()
{
}


BlankGame::~BlankGame()
{
}

bool BlankGame::loadContent()
{
	return true;
}

void BlankGame::unloadContent()
{
}

void BlankGame::update(float deltaTime)
{
}

void BlankGame::render()
{
	if(deviceContext == nullptr)
		return;

	float color[4] = { 0.0f, 0.0f, 0.f, 1.0f };
	deviceContext->ClearRenderTargetView(backBuffer, color);

	swapChain->Present(0, 0);
}