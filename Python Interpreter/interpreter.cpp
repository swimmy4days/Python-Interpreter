#include "type.h"
#include "parser.h"
#include <iostream>

#define WELCOME "Welcome to the Python Interperter version 1.0 by Ido"

int main(int argc,char** argv)
{
	string input_string;
	Type* temp;

	cout << WELCOME  << std::endl;

	// get new command from user
	cout << ">>> ";
	getline(cin, input_string);
	
	while (input_string != "quit()" && input_string != "exit()")
	{
		try
		{
			// prasing command
			temp = Parser::parseString(input_string);

			if (temp)
			{
				if (temp->getPrintable())
				{
					cout << temp->toString() << endl;
				}
				if (temp->getTemp())
				{
					delete temp;
				}
			}
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}


		// get new command from user
		cout << ">>> ";
		getline(cin, input_string);
	}

	Parser::freeAllVariables();

	return 0;
}
