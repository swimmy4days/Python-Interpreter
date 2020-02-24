#include "type.h"

Type::Type(char t)
{
	this->_isTemp = false;
	this->_holders = 1;

	if (t == 'i' || t == 'b' || t == 'l' || t == 'v' || t == 's' || t == 'c')
	{
		this->_type = t;
	}
	else
	{
		throw SyntaxException();
	}
}

bool Type::getTemp() const
{
	return this->_isTemp;
}

void Type::setTemp(bool state)
{
	this->_isTemp = state;
}

bool Type::getPrintable() const
{
	return true;
}

const char Type::whatType() const
{
	return this->_type;
}


void Type::incHolders()
{
	this->_holders += 1;
}

void Type::decHolders()
{
	this->_holders -= 1;
	if (this->_holders == 0)
	{
		this->setTemp(true);
	}
}
