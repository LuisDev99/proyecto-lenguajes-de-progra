#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <any>
#include "Parser.h"

using namespace std;

struct Token {


	Token() : priority(0) {

	}

	Token(int _value) : priority(0) {
		value = _value;
		strValue = std::to_string(_value);
	}

	Token(char _value) : priority(0) {
		value = _value;

		switch (_value) {

		case '(': case '[' :
			priority = Lowest;
			break;

		case '^':
			priority = Highest;
			break;

		case '*': case '/': case '%':
			priority = High;
			break;

		case '+': case '-':
			priority = Low;
			break;
		}

		strValue.push_back(_value);
	}

	Token(float _value) : priority(0) {
		value = _value;
		strValue = std::to_string(_value);
	}

	auto getValue() {
		return value;
	}

	string getType() {
		return value.type().name();
	}

	int getPriority() {
		return priority;
	}

	std::string to_string() {
		return strValue;
	}
	
private:
	any value;
	std::string strValue;
	int priority;
};


class InfixToPostFixConverter
{
public:
	InfixToPostFixConverter();
	InfixToPostFixConverter(std::string _infix);
	~InfixToPostFixConverter();


	std::string getPostFixExpression();

	char getTokenChar(Token t);

	void printStack(std::vector<Token> stacky);
	void convertInfixToPostFix();
	void printToken(Token t);

private:
	std::string postFix;
	std::string infix;
	std::vector<Token> tokens;
	std::vector<Token> postFixVector;

	void tokenizeInfixString();
	
};

