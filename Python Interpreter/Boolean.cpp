#include "Boolean.h"

Boolean::Boolean(bool value) : Type('b')
{
	this->_data = value;
}

string Boolean::toString() const
{
	return this->_data ? string("True") : string("False");
}