#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "type.h"

class Sequence : public Type
{
public:
	Sequence(char t);
	virtual string toString() const = 0;
	virtual unsigned int getLen() const = 0;
};

#endif // SEQUENCE_H