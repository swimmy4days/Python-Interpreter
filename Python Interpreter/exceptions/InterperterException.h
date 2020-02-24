#ifndef INTERPERTER_EXCEPTION_H
#define INTERPERTER_EXCEPTION_H

#include <exception>

class InterperterException : public std::exception
{
public:
	virtual const char* what() const;
};

#endif //INTERPERTER_EXCEPTION_H