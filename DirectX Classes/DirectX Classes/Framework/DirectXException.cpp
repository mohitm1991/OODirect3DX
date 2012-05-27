#include "Includes\DirectXException.h"

DirectXException::DirectXException() : errorMessage("")
{
}

DirectXException::DirectXException(char* reason) : errorMessage(reason)
{
}

const char* DirectXException::what()
{
	return errorMessage;
}