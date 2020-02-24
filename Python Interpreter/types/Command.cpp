#include "Command.h"

Command::Command(string data) : Type('c')
{
	this->_data = data;
	this->setTemp(true);
}

string Command::toString() const
{
	return this->_data;
}

bool Command::getPrintable() const
{
	return !this->_data.empty();
}
