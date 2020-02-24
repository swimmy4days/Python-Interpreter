#include "myString.h"

String::String(string data) : Sequence('s')
{
	this->_data = data.substr(1, data.size() - 2);
}

string String::toString() const
{
	return string('\'' + this->_data + '\'');
}

unsigned int String::getLen() const
{
	return this->_data.size();
}