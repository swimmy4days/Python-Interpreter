#ifndef TYPE_H
#define TYPE_H

#include <string>
#include "SyntaxException.h"

using std::string;
using std::to_string;

class Type
{
public:
	Type(char t);
	void incHolders();
	void decHolders();
	bool getTemp() const;
	void setTemp(bool state);
	const char whatType() const;
	virtual bool getPrintable() const;
	virtual string toString() const = 0;

private:
	short _holders;
	bool _isTemp;
	char _type;
};

#endif //TYPE_H
