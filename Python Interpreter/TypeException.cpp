#include "TypeException.h"

TypeException::TypeException(char type, const char* error)
{
	this->_error = "TypeError: object of type \'";

	switch (type)
	{
		break;
	case 'i':
		this->_error += "int";
		break;
	case 'l':
		this->_error += "list";
		break;
	case 'b':
		this->_error += "bool";
		break;
	case 'v':
		this->_error += "void";
		break;
	case 's':
		this->_error += "str";
		break;
	case 'c':
		this->_error += "command";
		break;
	default:
		throw SyntaxException();
		break;
	}

	this->_error += "\'";
	this->_error += " ";
	this->_error += error;
}

const char* TypeException::what() const throw()
{
	
	return (this->_error.c_str());
	//return "TypeError: object of type ‘int’ has no len()"
}
