#include "Parser.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

//Done: Implement validation of whether the input is in correct infix notation. Function: isCorrectInfixNotation
//TODO: 

Parser::Parser()
{
}

Parser::Parser(std::string _input) : input(_input)
{
	this->result = "0";

	getPostFixResult();

}

Parser::~Parser()
{
}

std::string Parser::getResult()
{
	return this->result;
}

void Parser::getPostFixResult()
{
	string userInputWarning = checkUserInput();

	/* If the user input doesn't satisfies the validations,
	   set the private variable result equal to the error message */
	if (userInputWarning != "Good Input") {
		cout << "\nIngreso mal la expresion! Intente de nuevo :D\n\n";
		setResult(userInputWarning);
		return;
	}

	this->result = "the arithmethic operation answer";
}

void Parser::setResult(std::string _result)
{
	this->result = _result;
}

std::string Parser::checkUserInput()
{

	/*Returns "Good Input" if the input satisfies every validation*/

	/* Supported Validations
	 * If the input has any other character rather than a digit or an arithmetic character
	 * If the parenthesis in the input are closed correctly and respectively
	 * If the curly brackets in the input are closed correctly and respectively
	 * If the input is in infix notation
	*/

	if (hasIllegalChar()) {
		return "Descripcion del error: Caracteres que no estan permitidos fueron ingresados";
	}

	if (!isOperandComplete('(', ')')) {
		return "Descripcion del error: Error de parentesis incompleto";
	}

	if (!isOperandComplete('[', ']')) {
		return "Descripcion del error: Error de corchetes incompleto";
	}

	if (!isCorrectInfixNotation()) {
		return "Descripcion del error: Expresion infija incorrecta";
	}


	return "Good Input";
}

bool Parser::hasIllegalChar()
{
	/* Returns true if the input has none digit characters except for the aithmetic operators and the '.' */

	for (int i = 0; i < input.size(); i++) {

		if ((!isdigit(input[i]) && input[i] != '.') && !isValidOperand(input[i])) {
			return true;
		}
	}
	return false;
}

bool Parser::isValidOperand(char str)
{
	/* Supported Operands:  "(),[],^,*,/,%,+,-" , every other character returns false */

	switch (str) {

	case '(': case ')': case '[': case ']': case '^': case '*': case '/': case '%': case '+': case '-':
		return true;
		break;

	default:
		return false;
		break;
	}
	return false;
}

bool Parser::isArithmeticOperand(char str) {

	switch (str) {

	case '^': case '*': case '/': case '%': case '+': case '-':
		return true;
		break;

	default:
		return false;
		break;
	}
	return false;
}

bool Parser::isOperandComplete(char leftOperand, char rightOperand)
{

	/* Returns true if the operand passed as parameter is opened and closed respectively */

	auto counter = [](string _input, char operand) { // C++ 11

		int operand_counter = (int)nullptr; //C++ 11

		for (char inputchar : _input) {

			if (inputchar == operand)
				operand_counter++;

		}

		return operand_counter;
	};

	auto leftOperandCounter = counter(input, leftOperand); //C++ 11
	auto rightOperandCounter = counter(input, rightOperand); //C++ 11


	return leftOperandCounter == rightOperandCounter;
}

bool Parser::isCorrectInfixNotation()
{
	/* Returns true if the input is not in postfix and prefix */

	/* Check if the first char or the last char of the user input is a parenthesis or curly bracket.
	 * If true, then the expression (the input) is infix
	 */

	if (isArithmeticOperand(input[0]) && isArithmeticOperand(input[input.size() - 1])) {
		return false;
	}

	/* Check if the infix notation is well written. Example: 4+3 -> valid. 4+3+ -> invalid. 4++3 -> invalid  */

	for (int i = 0; i < input.size(); i++) {

		/*Check if a arithmetic operator is being repeated twice in a row*/
		if (isArithmeticOperand(input[i])) {

			if ((i + 1) != input.size()) {

				if (isArithmeticOperand(input[i + 1])) // -> 4 + + 4 WRONG!
					return false;

			}

		// operator should have a number to its left side side -> ( + 4) WRONG!

		/* Examples that this verifies: (+4), +4, -4*/

		bool b1 = input[i - 1] == ')';
		bool b2 = input[i - 1] == ']';
		bool b3 = isdigit(input[i - 1]);

		if (b3)
			continue;

		bool b4 = (b1 || b2);


		if ( !b4 )
			return false;



		}
	}

	return true;
}
