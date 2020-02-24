#ifndef NAME_ERROR_EXCEPTION_H
#define NAME_ERROR_EXCEPTION_H

#include <string>
#include "InterperterException.h"

using std::string;

class NameErrorException : public InterperterException
{
public:
	NameErrorException(string name);
	virtual const char* what() const throw();
private:
	string _name;
};

#endif // NAME_ERROR_EXCEPTION_H