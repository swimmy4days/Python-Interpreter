#pragma once

#include <iostream>
#include "SyntaxException.h"
#include "InterperterException.h"

using std::string;

class TypeException : public InterperterException
{
public:
	TypeException(char type, const char* error);
	virtual const char* what() const throw();
private: 
	string _error;
};

