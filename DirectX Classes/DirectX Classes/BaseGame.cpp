#include "Includes\BaseGame.h"

BaseGame::BaseGame() : device(nullptr), deviceContext(nullptr), swapChain(nullptr), backBuffer(nullptr)
{
}

BaseGame::~BaseGame()
{
	shutdown();
}

bool BaseGame::initialize(HINSTANCE instance, HWND window)
{
	this->instance = instance;
	this->window = window;

	RECT dimensions;
	GetClientRect(window, &dimensions);
	int width = dimensions.right - dimensions.left;
	int height = dimensions.bottom - dimensions.top;

	deviceContext.reset(new DeviceContext());
	device.reset(new Device(deviceContext.get()));

	swapChain.reset(device->createSwapChain(width, height, 60, window));

	backBuffer.reset(device->createRenderTargetView(unique_ptr<const Resource>(swapChain->getBackBuffer()).get()));
	deviceContext->setRenderTarget(backBuffer.get());

	ViewPort viewPort;
	viewPort.setSize(width, height);
	viewPort.setDepth(0.0f, 1.0f);
	viewPort.setOrigin(0, 0);
	deviceContext->setViewPort(viewPort);

	return loadContent();
}

void BaseGame::shutdown()
{
	unloadContent();

	backBuffer.reset(nullptr);
	swapChain.reset(nullptr);
	deviceContext.reset(nullptr);
	device.reset(nullptr);
}

bool BaseGame::loadContent()
{
	return true;
}

void BaseGame::unloadContent()
{
}