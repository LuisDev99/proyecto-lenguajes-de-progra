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
	std::string getPostFix();
	std::string getErrorMessage();

	bool anErrorOccurred();

	static bool isArithmeticOperand(char str);
	static bool isValidOperand(char str);

	static void printColoredMessage(std::string message, int color);
	

private:
	std::string input;
	std::string result;
	std::string postFix;
	std::string errorMessage;
	std::vector<std::string> stack;
	std::vector<std::string> results;

	bool anErrorHappen;


	std::string checkUserInput();
	void getPostFixResult();
	void setResult(std::string _result);

	bool hasIllegalChar();
	bool isOperandComplete(char leftOperand, char rightOperand);
	bool isCorrectInfixNotation();

};

