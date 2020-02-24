#include "Integer.h"

Integer::Integer(int value) : Type('i')
{
	this->_data = value;
}

string Integer::toString() const
{
	return to_string(this->_data);
}