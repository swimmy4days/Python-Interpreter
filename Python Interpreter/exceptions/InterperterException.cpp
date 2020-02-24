#include "InterperterException.h"

const char* InterperterException::what() const
{
	return "IndentationError: unexpected indent";
}
