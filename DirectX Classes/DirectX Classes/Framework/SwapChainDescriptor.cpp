#include "Includes\SwapChainDescriptor.h"

SwapChainDescriptor::SwapChainDescriptor() : descriptor()
{
}

void SwapChainDescriptor::setBufferSize(int width, int height)
{
	descriptor.BufferDesc.Width = width;
	descriptor.BufferDesc.Height = height;
}

int SwapChainDescriptor::getBufferWidth() const
{
	return descriptor.BufferDesc.Width;
}

int SwapChainDescriptor::getBufferHeight() const
{
	return descriptor.BufferDesc.Height;
}

void SwapChainDescriptor::setRefreshRate(double refreshRate)
{
	double fractionalRate = refreshRate - static_cast<int>(refreshRate);
	int denominator = 1;
	while(fractionalRate > 0)
	{
		denominator *= 10;
		fractionalRate *= 10;
		fractionalRate -= static_cast<int>(fractionalRate);
	}

	descriptor.BufferDesc.RefreshRate.Numerator = static_cast<int>(refreshRate * denominator);
	descriptor.BufferDesc.RefreshRate.Denominator = denominator;
}

double SwapChainDescriptor::getRefreshRate() const
{
	return static_cast<double>(descriptor.BufferDesc.RefreshRate.Numerator)/descriptor.BufferDesc.RefreshRate.Denominator;
}

void SwapChainDescriptor::setBufferFormat(DXGI_FORMAT format)
{
	descriptor.BufferDesc.Format = format;
}

DXGI_FORMAT SwapChainDescriptor::getBufferFormat() const
{
	return descriptor.BufferDesc.Format;
}

void SwapChainDescriptor::setMultiSampling(int count, int quality)
{
	descriptor.SampleDesc.Count = count;
	descriptor.SampleDesc.Quality = quality;
}

int SwapChainDescriptor::getMultiSamplingCount() const
{
	return descriptor.SampleDesc.Count;
}

int SwapChainDescriptor::getMultiSamplingQuality() const
{
	return descriptor.SampleDesc.Quality;
}

void SwapChainDescriptor::setBufferUsage(DXGI_USAGE usage)
{
	descriptor.BufferUsage = usage;
}

DXGI_USAGE SwapChainDescriptor::getBufferUsage() const
{
	return descriptor.BufferUsage;
}

void SwapChainDescriptor::setBufferCount(int count)
{
	descriptor.BufferCount = count;
}

int SwapChainDescriptor::getBufferCount() const
{
	return descriptor.BufferCount;
}

void SwapChainDescriptor::setOutputWindow(HWND window)
{
	descriptor.OutputWindow = window;
}

HWND SwapChainDescriptor::getOutputWindow() const
{
	return descriptor.OutputWindow;
}

void SwapChainDescriptor::setWindowed(bool windowed)
{
	descriptor.Windowed = windowed;
}

bool SwapChainDescriptor::isWindowed() const
{
	return descriptor.Windowed;
}