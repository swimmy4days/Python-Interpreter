#ifndef VOID_H
#define VOID_H

#include "type.h"

class Void : public Type
{
public:
	Void();
	bool getPrintable() const;
	virtual string toString() const;
};

#endif // VOID_H