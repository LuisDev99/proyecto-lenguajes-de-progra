#include "InfixToPostFixConverter.h"
#include <regex>
#include <iterator>
#include <iostream>
#include <string>
#include <stack>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include "Parser.h"

InfixToPostFixConverter::InfixToPostFixConverter()
{
}

InfixToPostFixConverter::InfixToPostFixConverter(std::string _infix)
{
	this->infix = _infix;
	convertInfixToPostFix();
	
}


InfixToPostFixConverter::~InfixToPostFixConverter()
{
}

std::string InfixToPostFixConverter::getPostFixExpression()
{
	return this->postFix;
	stack<int> hi;
}

void InfixToPostFixConverter::printToken(Token t)
{
	string str;
	if (t.getType() == "int") {
		str = to_string(any_cast<int>(t.getValue()));
	} else if (t.getType() == "float") {
		str = to_string(any_cast<float>(t.getValue()));
	} else {
		str = any_cast<char>(t.getValue());
	}

	cout << t.getType() << ": " <<str << endl;
}

char InfixToPostFixConverter::getTokenChar(Token t)
{
	return any_cast<char>(t.getValue());
}

void InfixToPostFixConverter::printStack(std::vector<Token> stacky)
{
	string str = "";

	if (stacky.empty()) {
		cout << "Vacia!" << endl;
		return;
	}

	for (auto t : boost::adaptors::reverse(stacky)) {

		string newStr;
		newStr.push_back(getTokenChar(t));

		str += "|              |\n";
		str += "|              |\n";
		str += "|              |\n";
		str += "|        "+newStr+"     |\n";
		str += "|              |\n";
		str += "|______________|\n";
	}

	cout << str << endl;
}

void InfixToPostFixConverter::convertInfixToPostFix()
{

	tokenizeInfixString(); 


	/* Following the algorithm mention here: https://www.includehelp.com/c/infix-to-postfix-conversion-using-stack-with-c-program.aspx */
	// Actual helpfull algorithm: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/

	vector<Token> stacky;


	/* Add parenthesis to the entire expression */
	stacky.push_back(Token('(')); 
	tokens.push_back(Token(')'));

	for (Token t : tokens) {

		printToken(t);

		if (t.getType() == "int") { 

			postFix += to_string(any_cast<int>(t.getValue()));
			postFix += ",";
			postFixVector.push_back(t);
		}  else if (t.getType() == "float") {

			postFix += to_string(any_cast<float>(t.getValue()));
			postFix += ",";
			postFixVector.push_back(t);
		} else { //if an operator is encountered

			/*The whole purpose of this project */

			if (t.to_string() == "(") {
				stacky.push_back(t);
			} else if (t.to_string() == "[") {
				stacky.push_back(t);

			} else if (t.to_string() == ")") {

				/* If a right parenthesis is encountered ,then:
					Repeatedly pop from Stack and add to Y each operator (on the top of Stack) until a left parenthesis is encountered.
					Remove the left Parenthesis.
					[End of If] [End of If]
				*/

				while (getTokenChar(stacky.back()) != '(') {
					
					string popItem;
					postFix.push_back(getTokenChar(stacky.back()));
					postFix += ",";

					if(getTokenChar(t) != ')')
						postFixVector.push_back(t);

					stacky.pop_back();
				}

				stacky.pop_back(); //Remove parenthesis

			} else if (t.to_string() == "]") {

				while (getTokenChar(stacky.back()) != '[') {

					string popItem;
					postFix.push_back(getTokenChar(stacky.back()));
					postFix += ",";
					postFixVector.push_back(t);
					stacky.pop_back();
				}

				stacky.pop_back(); //Remove parenthesis

			} else {

				// 4^2*3-3+8/4/(1+1)

				/*.3.1 If the precedence of the scanned operator is greater than the precedence of the operator in the stack(or the stack is empty or the stack contains a ‘(‘), push it.
					…..3.2 Else, Pop all the operators from the stack which are greater than or equal to in precedence than that of the scanned operator. After doing that Push the scanned operator to the stack. (If you encounter parenthesis while popping then stop there and push the scanned operator in the stack.) */
		
				if (t.getPriority() > stacky.back().getPriority()) {

					stacky.push_back(t);
				} else {

					while (t.getPriority() <= stacky.back().getPriority()) {

						if (getTokenChar(stacky.back()) == '(' || getTokenChar(stacky.back()) == '[')
							break;

						string popItem;
						postFix.push_back(getTokenChar(stacky.back()));
						postFix += ",";
						postFixVector.push_back(t);
						stacky.pop_back();

					}

					stacky.push_back(t);
				}

			}
		
		}

		cout << "Estado del Postfijo: " << postFix << endl;

		cout << "Estado de la pila ->\n";
		printStack(stacky);

	}
  
	/*cout << postFix << endl;*/
}

void InfixToPostFixConverter::tokenizeInfixString()
{

	/* Separate every int or float or operator from the infix input into a single string using regular expression and store it in the vector untokenize */
	
	vector<string> untokenize;
	string printer;
	std::regex words_regex("[0-9]?([0-9]*[.])?[0-9]+|[\\[\\]\\^\\-\\+\\\\\(\\)\\/\\*]"); 
	auto words_begin = std::sregex_iterator(infix.begin(), infix.end(), words_regex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		untokenize.push_back((*i).str());
	}

	printer = "Tipos encontrados: ";

	/* Populate the tokens vector */

	for (string str : untokenize) {

		Token newToken;

		if (str.find('.') != string::npos) { // Checking to see if its a floating number by seeing if the current string has a char equal to '.' 

			float n = boost::lexical_cast<float>(str);
			newToken = Token(n);
			printer += "Flotante ";

		} else if (Parser::isValidOperand(str[0])) { //Checking if its a operator

			newToken = Token(str[0]);
			printer += "Operador" + str + " ";

		} else { //Its a int

			int n = boost::lexical_cast<int>(str);
			newToken = Token(n);
			printer += "Entero ";

		}

		tokens.push_back(newToken);
	}

	cout << printer << endl;
}
