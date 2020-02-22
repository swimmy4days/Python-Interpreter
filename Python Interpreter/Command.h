#pragma once

#include "type.h"

class Command :	public Type
{
public:
	Command(string data);
	virtual string toString() const;
	virtual bool getPrintable() const;
private:
	string _data;
};

