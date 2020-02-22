#ifndef INTEGER_H
#define INTEGER_H

#include "type.h"

class Integer : public Type
{
public:
	Integer(int value);
	virtual string toString() const;

private:
	int _data;
};

#endif // INTEGER_H