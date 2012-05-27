#ifndef DIRECTX_INPUT_ELEMENT_DESCRIPTOR
#define DIRECTX_INPUT_ELEMENT_DESCRIPTOR

#include <D3D11.h>

class InputElementDescriptor
{
	friend class Device;
	private:
		D3D11_INPUT_ELEMENT_DESC descriptor;
	public:
		InputElementDescriptor();
		InputElementDescriptor(D3D11_INPUT_ELEMENT_DESC descriptor);
		InputElementDescriptor(const char* elementName, int elementIndex, DXGI_FORMAT format, int inputSlot, int byteOffset, bool perVertex, int stepRate);

		void setElementName(const char* name);
		const char* getElementName();

		void setElementIndex(int index);
		int getElementIndex();

		void setFormat(DXGI_FORMAT format);
		DXGI_FORMAT getFormat();

		void setInputSlot(int inputSlot);
		int getInputSlot();

		void setByteOffset(int offset);
		int getByteOffset();

		void setPerVertex(bool perVertex);
		bool isPerVertex();

		void setStepRate(int stepRate);
		int getStepRate();
};

#endif