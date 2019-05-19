#pragma once

#include <string>
#include <vector>

enum Priority
{
	Highest = 4,  //
	High = 3, // % * /
	Low = 2,  // + - 
	Lowest = 1
};

class Parser
{
public:
	Parser();
	Parser(std::string _input);
	~Parser();

	std::string getResult();

	static bool isArithmeticOperand(char str);
	static bool isValidOperand(char str);
	

private:
	std::string input;
	std::string result;
	std::vector<std::string> stack;
	std::vector<std::string> results;


	std::string checkUserInput();
	void getPostFixResult();
	void setResult(std::string _result);

	bool hasIllegalChar();
	bool isOperandComplete(char leftOperand, char rightOperand);
	bool isCorrectInfixNotation();

};

