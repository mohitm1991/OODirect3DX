#include "Includes\InputElementDescriptor.h"

InputElementDescriptor::InputElementDescriptor() : descriptor()
{
}

InputElementDescriptor::InputElementDescriptor(D3D11_INPUT_ELEMENT_DESC desc) : descriptor(desc)
{
}

InputElementDescriptor::InputElementDescriptor(const char* elementName, int elementIndex, DXGI_FORMAT format, int inputSlot, int byteOffset, bool perVertex, int stepRate) : descriptor()
{
	setElementName(elementName);
	setElementIndex(elementIndex);
	setFormat(format);
	setInputSlot(inputSlot);
	setByteOffset(byteOffset);
	setPerVertex(perVertex);
	setStepRate(stepRate);
}

void InputElementDescriptor::setElementName(const char* name)
{
	descriptor.SemanticName = name;
}

const char* InputElementDescriptor::getElementName()
{
	return descriptor.SemanticName;
}

void InputElementDescriptor::setElementIndex(int index)
{
	descriptor.SemanticIndex = index;
}

int InputElementDescriptor::getElementIndex()
{
	return descriptor.SemanticIndex;
}

void InputElementDescriptor::setFormat(DXGI_FORMAT format)
{
	descriptor.Format = format;
}

DXGI_FORMAT InputElementDescriptor::getFormat()
{
	return descriptor.Format;
}

void InputElementDescriptor::setInputSlot(int inputSlot)
{
	descriptor.InputSlot = inputSlot;
}

int InputElementDescriptor::getInputSlot()
{
	return descriptor.InputSlot;
}

void InputElementDescriptor::setByteOffset(int byteOffset)
{
	descriptor.AlignedByteOffset = byteOffset;
}

int InputElementDescriptor::getByteOffset()
{
	return descriptor.AlignedByteOffset;
}

void InputElementDescriptor::setPerVertex(bool perVertex)
{
	if(perVertex)
		descriptor.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	else
		descriptor.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
}

bool InputElementDescriptor::isPerVertex()
{
	return descriptor.InputSlotClass == D3D11_INPUT_PER_VERTEX_DATA ? true : false;
}

void InputElementDescriptor::setStepRate(int stepRate)
{
	descriptor.InstanceDataStepRate = stepRate;
}

int InputElementDescriptor::getStepRate()
{
	return descriptor.InstanceDataStepRate;
}