#ifndef DIRECTX_EXCEPTION
#define DIRECTX_EXCEPTION

#include <exception>
using std::exception;

class DirectXException : public exception
{
	private:
		char* errorMessage;
	public:
		DirectXException();
		DirectXException(char* reason);

		virtual const char* what();
};

#endif