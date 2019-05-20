#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <any>
#include "Parser.h"
#include <Windows.h>
using namespace std;

struct Token {


	Token() = default;

	Token(int _value) : priority(0) {
		value = _value;
		strValue = std::to_string(_value);
	}

	Token(char _value) : priority(0) {
		value = _value;

		switch (_value) {

		case '(': case '[' :
			priority = (int)Priority::Lowest;
			break;

		case '^':
			priority = (int)Priority::Highest;
			break;

		case '*': case '/': case '%':
			priority = (int)Priority::High;
			break;

		case '+': case '-':
			priority = (int)Priority::Low;
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
	std::string strValue = "";
	int priority = 0;
};


class InfixToPostFixConverter
{
public:
	InfixToPostFixConverter();
	InfixToPostFixConverter(std::string _infix);
	~InfixToPostFixConverter();


	std::string getPostFixExpression(); // c++14 -> old: std::string getPostFixExpression() {} en la definicion
	std::string getPostFixResult();
	std::string getErrorMessage();

	char getTokenChar(Token t);
	float getTokenFloat(Token t);
	int getTokenInt(Token t);

	bool didSemanticErrorOcurred();

	Token operateTokens(Token n1, Token n2, char arithmeticOperator);

	void printStackBeauty(std::vector<Token> stacky);
	void convertInfixToPostFix();
	void printToken(Token t);

	void evaluatePostFix();

private:
	bool semanticError = false;

	std::string errorMessage = "";
	std::string postFix ="", postFixResult="";
	std::string infix ="";
	std::vector<Token> tokens;
	std::vector<Token> postFixVector;

	void tokenizeInfixString();
	
};

