#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>
#include <sstream>
#include "Includes\BaseGame.h"
#include "Includes\BlankGame.h"
#include "Includes\TriangleGame.h"
#include "Includes\TextureGame.h"
#include "Includes\SpriteGame.h"
using std::unique_ptr;
using std::stringstream;

HWND initializeWindow(HINSTANCE instance, int width, int height, int windowState);
LRESULT CALLBACK windowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

void initializeDirect3D(HWND window, int width, int height);
void renderScene();
void closeDirect3D();

int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE previousInstance, LPWSTR commandLine, int windowState)
{
	const int WIDTH = 600;
	const int HEIGHT = 600;
	
	HWND window = initializeWindow(instance, WIDTH, HEIGHT, windowState);
	
	SpriteGame gameObject;
	
	bool success = gameObject.initialize(instance, window);
	if(!success)
		return -1;
	
	MSG message = {0};
	while(message.message != WM_QUIT)
	{
		if(PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		gameObject.update(0.0f);
		gameObject.render();
	}

	gameObject.shutdown();

	return static_cast<int>(message.wParam);
}

HWND initializeWindow(HINSTANCE instance, int width, int height, int windowState)
{
	HWND window;
	WNDCLASSEX windowClass = {0};

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = windowProcedure;
	windowClass.hInstance = instance;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = "Window Class";
	RegisterClassEx(&windowClass);

	RECT rectangle = {0, 0, width, height};
	AdjustWindowRect(&rectangle, WS_OVERLAPPEDWINDOW, false);
	window = CreateWindowA("Window Class", "Direct3D Program", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, nullptr, nullptr, instance, nullptr);
	ShowWindow(window, windowState);

	return window;
}

LRESULT CALLBACK windowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_PAINT:
			PAINTSTRUCT paintStructure;
			BeginPaint(window, &paintStructure);
			EndPaint(window, &paintStructure);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(window, message, wParam, lParam);
	}

	return 0;
}