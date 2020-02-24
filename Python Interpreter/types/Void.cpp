#include "Void.h"

Void::Void() : Type('v')
{
	
}

bool Void::getPrintable() const
{
	return false;
}

string Void::toString() const
{
	return string();
}