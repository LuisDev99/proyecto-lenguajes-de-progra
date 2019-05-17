#pragma once

#include <string>
#include <vector>
class Parser
{
public:
	Parser();
	Parser(std::string _input);
	~Parser();

	std::string getResult();
	

private:
	std::string input;
	std::string result;
	std::vector<std::string> stack;
	std::vector<std::string> results;


	std::string checkUserInput();
	void getPostFixResult();
	void setResult(std::string _result);

	bool hasIllegalChar();
	bool isValidOperand(char str);
	bool isArithmeticOperand(char str);
	bool isOperandComplete(char leftOperand, char rightOperand);
	bool isCorrectInfixNotation();

};

