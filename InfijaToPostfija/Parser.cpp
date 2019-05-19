#include "Parser.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "InfixToPostFixConverter.h"

#define RED 12
#define GREEN 10
#define BLUE 9

using namespace std;

//Done: Implement validation of whether the input is in correct infix notation. Function: isCorrectInfixNotation
//TODO: 

Parser::Parser()
{
}

Parser::Parser(std::string _input) : input(_input)
{
	this->result = "0";
	anErrorHappen = false;
	errorMessage = "";

	getPostFixResult();

}

Parser::~Parser()
{
}

std::string Parser::getResult()
{
	return this->result;
}

std::string Parser::getPostFix()
{
	return this->postFix;
}

std::string Parser::getErrorMessage()
{
	return this->errorMessage;
}

bool Parser::anErrorOccurred()
{
	return this->anErrorHappen;
}

void Parser::getPostFixResult()
{
	string userInputWarning = checkUserInput();

	/* If the user input doesn't satisfies the validations, set the private variable result equal to the error message */
	if (userInputWarning != "Good Input") {
		cout << "\nIngreso mal la expresion! Intente de nuevo :D\n\n";
		anErrorHappen = true;
		this->errorMessage = userInputWarning;
		return;
	}

	InfixToPostFixConverter converter(this->input); //Converts the infix expression to postfix expression and also the answer to the expression

	if (converter.didSemanticErrorHappen()) {
		cout << "\nIngreso mal la expresion! Intente de nuevo :D\n\n";
		anErrorHappen = true;
		this->errorMessage = converter.getErrorMessage();
		return;
	}

	this->result = converter.getPostFixResult();
	this->postFix = converter.getPostFixExpression();
}

void Parser::setResult(std::string _result)
{
	this->result = _result;
}

std::string Parser::checkUserInput()
{

	//TODO: 3+13+1+3()

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

void Parser::printColoredMessage(std::string message, int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Print with desired color
	SetConsoleTextAttribute(hConsole, color);

	cout << message << endl;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Reset to White
	SetConsoleTextAttribute(hConsole, 7);
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

	auto counter = [](string _input, char operand) { // C++ 11 CON C++14

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

	if (isArithmeticOperand(input[0]) || isArithmeticOperand(input[input.size() - 1])) {
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

		// operator NEEDS to have a number to its left side side -> ( + 4) WRONG!

		/* Examples that this verifies: (+4), +4, -4*/

		bool b1 = input[i - 1] == ')';
		bool b2 = input[i - 1] == ']';
		bool b3 = isdigit(input[i - 1]);

		if (b3) // If an arithmetic operand is found and a digit is in its left side, then the input is good, so continue evaluating
			continue;

		bool b4 = (b1 || b2); // If an arithmetic operand is found and the character behind isnt a closing parenthesis or closing curly bracket, then the input is bad


		if ( !b4 )
			return false;

		}
	}

	return true;
}
