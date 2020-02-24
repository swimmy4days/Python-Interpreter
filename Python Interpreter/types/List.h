#ifndef LIST_H
#define LIST_H

#include <vector>
#include <iostream>
#include "parser.h"
#include "Helper.h"
#include "Sequence.h"
#include "SyntaxException.h"

using std::cout;
using std::endl;
using std::vector;

class List : public Sequence
{
public:
	List(string data);
	virtual string toString() const;
	virtual unsigned int getLen() const;

private:
	vector<Type*> _data;
};	

#endif // LIST_H