#include "NameErrorException.h"

NameErrorException::NameErrorException(string name)
{
	this->_name = "NameError: name \'";
	this->_name += name;
	this->_name += "\' is not defined";
}

const char* NameErrorException::what() const throw()
{
	return this->_name.c_str();
}
