#ifndef BaseGame_H_
#define BaseGame_H_

#include <D3DX11.h>
#include <atlbase.h>

class BaseGame
{
	protected:
		HINSTANCE instance;
		HWND window;

		CComPtr<ID3D11Device> device;
		CComPtr<ID3D11DeviceContext> deviceContext;
		CComPtr<IDXGISwapChain> swapChain;
		CComPtr<ID3D11RenderTargetView> backBuffer;
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