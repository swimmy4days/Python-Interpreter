#ifndef STRING_H
#define STRING_H

#include "Sequence.h"

class String : public Sequence
{
public:
	String(string data);
	virtual string toString() const;
	virtual unsigned int getLen() const;

private:
	string _data;
};

#endif // STRING_H