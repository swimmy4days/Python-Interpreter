#include "List.h"

List::List(string data) : Sequence('l')
{
	string temp = data.substr(1, data.size() - 2);
	string::size_type commaPos;
	string item;
	Type* type;

	Helper::trim(temp);
	if (temp.size() > 0)
	{
		commaPos = temp.find(',');
		if (commaPos != string::npos)
		{
			while (commaPos != string::npos)
			{
				commaPos = temp.find(',');
				item = temp.substr(0, commaPos);
				temp = temp.substr(commaPos + 1);
				Helper::trim(temp);
				Helper::trim(item);
				if (item.size() == 0)
				{
					for (auto p : this->_data)
					{
						delete p;
					}
					this->_data.clear();
					throw SyntaxException();
				}
				type = Parser::getType(item);
				if (type)
				{
					this->_data.push_back(type);
				}
				else
				{
					for (auto& p : this->_data)
					{
						delete p;
					}
					this->_data.clear();
					throw SyntaxException();
				}
			}
		}
		else
		{
			this->_data.push_back(Parser::getType(temp));
			//throw SyntaxException();
		}
	}
	else
	{
		this->_data.push_back(new Void());
	}
	//this->_data = data;
}

string List::toString() const
{
	string temp = "[";
	bool flag = false;

	for (auto& i : this->_data)
	{
		temp += i->toString();
		temp += ", ";
		flag = true;
	}

	if (flag)
	{
		temp = temp.substr(0, temp.size() - 2);
	}

	temp += "]";

	return temp;
}

unsigned int List::getLen() const
{
	if (this->_data.size() == 1 && (this->_data[0])->whatType() == 'v')
	{
		return 0;
	}
	return this->_data.size();
}
