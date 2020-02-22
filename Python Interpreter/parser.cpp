#include "parser.h"
#include <iostream>

unordered_map<string, Type*> Parser::_variables;

Type* Parser::parseString(string str)
{
	Type* temp = NULL;
	if (str.length() > 0)
	{
		if (str[0] == ' ' || str[0] == '\t')
		{
			throw IndentationException();
		}
		Helper::trim(str);
		temp = Parser::commands(str);
		if (!temp && !Parser::makeAssignment(str))
		{
			temp = Parser::getVariableValue(str);
		}
	}

	return temp;
}

Type* Parser::getType(string str)
{
	Helper::trim(str);

	if (str[0] == '[' && str.find(']', 1))
	{
		bool open = false;
		bool close = false;

		for (auto& i : str)
		{
			if (i == '[')
			{
				if (!open)
				{
					open = true;
				}
				else
				{
					throw SyntaxException();
				}
			}
			else if (i == ']')
			{
				if (!close)
				{
					close = true;
				}
				else
				{
					throw SyntaxException();
				}
			}
		}
		return new List(str);
	}
	else if (Helper::isInteger(str))
	{
		return new Integer(stoi(str));
	}
	else if (Helper::isBoolean(str))
	{
		if (str == "True")
		{
			return new Boolean(true);
		}
		return new Boolean(false);
	}
	else if (Helper::isString(str))
	{
		return new String(str);
	}

	return NULL;
}

bool Parser::isLegalVarName(const std::string& str)
{
	if (str == "type" || str == "len" || str == "del")
	{
		throw TypeException('c', "cannot be assigned");
	}
	for (size_t i = 0; i < str.length(); i++)
	{
		char c = str[i];
		if (i == 0 && (c >= '0' && c <= '9'))
		{
			return false;
		}
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') && (c >= '0' && c <= '9') || (c == '_'))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Parser::makeAssignment(const string& str)
{
	unordered_map<string, Type*>::iterator it;
	bool equals = false;
	size_t index = 0;
	Type* value = 0;
	string type;
	string var;

	for (auto& letter : str)
	{
		if (letter == '=')
		{
			if (!equals)
			{
				equals = true;
			}
			else
			{
				return false;
			}
		}
	}
	if (!equals)
	{
		return false;
	}

	index = str.find('=');
	var = str.substr(0, index);
	type = str.substr(index + 1);

	Helper::trim(var);
	Helper::trim(type);

	if (!Parser::isLegalVarName(var))
	{
		throw SyntaxException();
	}

	if (Parser::isLegalVarName(type))
	{
		Type* temp = Parser::getVariableValue(type);
		if (temp->whatType() == 'l')
		{
			value = temp;
			value->incHolders();
		}
		else if (temp && temp->getPrintable())
		{
			value = Parser::getType((temp->toString()));
		}
		else
		{
			throw NameErrorException(type);
		}
	}
	else
	{
		if (type.length() != 0)
		{
			value = Parser::getType(type);
			if (!value)
			{
				throw SyntaxException();
			}
		}
		else
		{
			throw SyntaxException();
		}
	}

	it = Parser::_variables.find(var);
	if (it != Parser::_variables.end())
	{
		(*it).second->decHolders();
		if ((*it).second->getTemp())
		{
			delete Parser::_variables.at(var);
			Parser::_variables.erase(it);
		}
	}
	Parser::_variables[var] = value;

	return true;
}

Type* Parser::getVariableValue(const string& str)
{
	unordered_map<string, Type*>::iterator it;
	Type* temp = 0;

	if (Parser::isLegalVarName(str))
	{
		it = Parser::_variables.find(str);
		if (it != Parser::_variables.end())
		{
			temp = Parser::_variables.at(str);
		}
		else
		{
			if (str.size() == 0)
			{
				throw SyntaxException();
			}
			throw NameErrorException(str);
		}
	}
	else
	{
		throw SyntaxException();
	}

	return temp;
}

void Parser::freeAllVariables()
{
	for (auto it = Parser::_variables.begin(); it != Parser::_variables.end(); ++it)
	{
		delete it->second;
	}
}

Type* Parser::typeCommand(string str)
{
	size_t pos = str.find("type(");
	string msg = "<type \'";
	Type* temp = 0;
	string var;

	if (!pos && str.find(")", str.size() - 1))
	{
		var = str.substr(5, str.size() - 6);
		temp = Parser::lenCommand(var);
		if (!temp)
		{
			if (Parser::_variables.find(var) != Parser::_variables.end())
			{
				temp = Parser::_variables.at(var);
			}
			else
			{

				if (Parser::isLegalVarName(var))
				{
					throw NameErrorException(var);
				}
				else
				{
					temp = Parser::getType(var);
					temp->setTemp(true);
				}
			}
		}
		switch (temp->whatType())
		{
		case 'i':
			msg += "int";
			break;
		case 'l':
			msg += "list";
			break;
		case 'b':
			msg += "bool";
			break;
		case 'v':
			msg += "void";
			break;
		case 's':
			msg += "str";
			break;
		default:
			throw SyntaxException();
			break;
		}
		msg += "\'>";

		if (temp->getTemp())
		{
			delete temp;
		}
		temp = new Command(msg);
	}
	return temp;
}

Type* Parser::lenCommand(string str)
{
	size_t pos = str.find("len(");
	pair<char, const char*> error;
	Type* temp = NULL;
	Type* len = NULL;
	string var;

	if (!pos && str.find(")", str.size() - 1))
	{
		var = str.substr(4, str.size() - 5);
		if (Parser::_variables.find(var) != Parser::_variables.end())
		{
			temp = Parser::_variables.at(var);
		}
		else
		{
			if (Helper::isDigit(var[0]))
			{
				throw TypeException('i', "Has no len()");
			}
			if (Parser::isLegalVarName(var))
			{
				throw NameErrorException(var);
			}
			else
			{
				temp = Parser::getType(var);
				temp->setTemp(true);
			}
		}

		if (temp->whatType() == 's' || temp->whatType() == 'l')
		{
			len = Parser::getType(to_string(((Sequence*)temp)->getLen()));
			len->setTemp(true);
		}
		else
		{
			error = make_pair(temp->whatType(), "Has no len()");
		}
		if (temp && temp->getTemp())
		{
			delete  temp;
		}
		if (error.first)
		{
			throw TypeException(error.first, error.second);
		}
	}
	return len;
}

Type* Parser::delCommand(string str)
{
	Type* temp = NULL;
	size_t pos = str.find("del ");
	string var;

	if (pos != string::npos)
	{
		var = str.substr(pos + 4);
		temp = Parser::getVariableValue(var);
		if (temp)
		{
			temp->decHolders();
			if (temp->getTemp())
			{
				delete temp;
			}
			Parser::_variables.erase(var);
			temp = new Command(string());
		}
		else
		{
			temp = 0;
		}
	}

	return temp;
}

//Type* Parser::commands(string str)
Type* Parser::commands(string str)
{
	Type* temp;
	if (str == "len" || str == "type" || str == "del")
	{
		temp = new Command(string("<built-in function " + string(str) + ">"));
		return temp;
	}
	temp = delCommand(str);
	if (!temp)
	{
		temp = Parser::lenCommand(str);
		if (!temp)
		{
			temp = Parser::typeCommand(str);
		}
	}
	return temp;
}
