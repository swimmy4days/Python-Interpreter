#ifndef PARSER_H
#define PARSER_H

#include "type.h"
#include "List.h"
#include "Void.h"
#include <string>
#include <sstream>
#include <iostream>
#include "String.h"
#include "Helper.h"
#include "Command.h"
#include "Boolean.h"
#include "Integer.h"
#include <unordered_map>
#include "TypeException.h"
#include "SyntaxException.h"
#include "NameErrorException.h"
#include "InterperterException.h"
#include "IndentationException.h"

using std::cout;
using std::cin;
using std::stoi;
using std::endl;
using std::pair;
using std::getline;
using std::make_pair;
using std::exception;
using std::unordered_map;

class Parser
{
public:
	static void freeAllVariables();
	static Type* getType(string str);
	static Type* commands(string str);
	static Type* parseString(string str);

private:
	static Type* delCommand(string str);
	static Type* lenCommand(string str);
	static Type* typeCommand(string str);
	static bool isLegalVarName(const string& str);
	static bool makeAssignment(const string& str);
	static Type* getVariableValue(const string& str);

	static unordered_map<string, Type*> _variables;
};

#endif //PARSER_H
