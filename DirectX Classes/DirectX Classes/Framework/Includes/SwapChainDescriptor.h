#ifndef DIRECTX_SWAP_CHAIN_DESCRIPTOR
#define DIRECTX_SWAP_CHAIN_DESCRIPTOR

#include <DXGI.h>

class SwapChainDescriptor
{
	friend class Device;

	private:
		DXGI_SWAP_CHAIN_DESC descriptor;
	public:
		SwapChainDescriptor();

		void setBufferSize(int width, int height);
		int getBufferWidth() const;
		int getBufferHeight() const;

		void setRefreshRate(double refreshRate);
		double getRefreshRate() const;

		void setBufferFormat(DXGI_FORMAT format);
		DXGI_FORMAT getBufferFormat() const;

		void setMultiSampling(int count, int quality);
		int getMultiSamplingCount() const;
		int getMultiSamplingQuality() const;

		void setBufferUsage(DXGI_USAGE usage);
		DXGI_USAGE getBufferUsage() const;

		void setBufferCount(int count);
		int getBufferCount() const;

		void setOutputWindow(HWND window);
		HWND getOutputWindow() const;

		void setWindowed(bool windowed);
		bool isWindowed() const;
};

#endif