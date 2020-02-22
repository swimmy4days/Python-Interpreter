#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "type.h"

class Boolean : public Type
{
public:
	Boolean(bool data);
	virtual string toString() const;

private:
	bool _data;
};

#endif // BOOLEAN_H