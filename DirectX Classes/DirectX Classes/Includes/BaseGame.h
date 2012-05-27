#ifndef BaseGame_H_
#define BaseGame_H_

#include "..\Framework\Includes\DirectX.h"
#include <memory>
using std::unique_ptr;

class BaseGame
{
	protected:
		HINSTANCE instance;
		HWND window;

		unique_ptr<Device> device;
		unique_ptr<DeviceContext> deviceContext;
		unique_ptr<SwapChain> swapChain;
		unique_ptr<RenderTargetView> backBuffer;
	public:
		BaseGame();
		virtual ~BaseGame();

		bool initialize(HINSTANCE instance, HWND window);
		void shutdown();

		virtual bool loadContent();
		virtual void unloadContent();

		virtual void update(float deltaTime) = 0;
		virtual void render() = 0;
};

#endif