#ifndef DIRECTX_VIEWPORT
#define DIRECTX_VIEWPORT

#include <D3D11.h>

class ViewPort
{
	friend class DeviceContext;

	private:
		D3D11_VIEWPORT viewPort;
	public:
		ViewPort();

		void setSize(int width, int height);
		int getWidth();
		int getHeight();

		void setDepth(float minDepth, float maxDepth);
		float getMinDepth();
		float getMaxDepth();

		void setOrigin(int topLeftX, int topLeftY);
		int getOriginX();
		int getOriginY();
};

#endif