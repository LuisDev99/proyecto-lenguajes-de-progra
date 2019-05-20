#include "InfixToPostFixConverter.h"
#include <regex>
#include <iterator>
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <math.h>
#include <Windows.h>
#include "Parser.h"

InfixToPostFixConverter::InfixToPostFixConverter()
{
}

InfixToPostFixConverter::InfixToPostFixConverter(std::string _infix)
{
	this->infix = _infix;
	semanticError = false;

	convertInfixToPostFix();
	
}


InfixToPostFixConverter::~InfixToPostFixConverter()
{
}

string InfixToPostFixConverter::getPostFixExpression()
{
	return this->postFix;
}

string InfixToPostFixConverter::getPostFixResult()
{
	return this->postFixResult;
}

string InfixToPostFixConverter::getErrorMessage()
{
	return this->errorMessage;
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

void InfixToPostFixConverter::evaluatePostFix()
{

	vector<Token> results;

	for (int i = 0; i < postFixVector.size(); i++) {

		if (postFixVector[i].getType() == "char") { 

			string arithmeticOperator;
			arithmeticOperator.push_back(getTokenChar(postFixVector[i])); //Append a char to the string

			Token n2 = results.back();
			results.pop_back();

			Token n1 = results.back();
			results.pop_back();

			Token result = operateTokens(n1, n2, arithmeticOperator[0]);
			results.push_back(result);

		} else {
			results.push_back(postFixVector[i]);
		}

	}

	this->postFixResult = results[0].to_string();

	//cout << "El resultado es: " << results[0].to_string() << endl;
}

char InfixToPostFixConverter::getTokenChar(Token t)
{
	return any_cast<char>(t.getValue());
}

float InfixToPostFixConverter::getTokenFloat(Token t)
{
	return any_cast<float>(t.getValue());
}

int InfixToPostFixConverter::getTokenInt(Token t)
{
	return any_cast<int>(t.getValue());
}

bool InfixToPostFixConverter::didSemanticErrorOcurred()
{
	return this->semanticError;
}

auto KeyGenerator() {

	int arithmeticOperator = 2 % sizeof(Token);
	return arithmeticOperator;
}

Token InfixToPostFixConverter::operateTokens(Token n1, Token n2, char arithmeticOperator)
{
	Token newT;
	int casty = 0, power = 0, modulus = 0;
	float powerf = 0;

	if (n1.getType() == "float" || n2.getType() == "float") {

		float f1 = (n1.getType() == "float") ? getTokenFloat(n1) : (float)getTokenInt(n1); //If the token isnt a float, then make a cast
		float f2 = (n2.getType() == "float") ? getTokenFloat(n2) : (float)getTokenInt(n2);

		switch (arithmeticOperator) {

		case '+':
			newT = Token(f1 + f2);
			break;

		case '-':
			newT = Token(f1 - f2);
			break;

		case '*':
			newT = Token(f1 * f2);
			break;

		case '/':
			newT = Token(f1 / f2);
			break;

		case '%':
			casty = (int)f1 % (int)f2;
			newT = Token((float)casty);
			break;

		case '^':
			powerf = pow(f1, f2);
			newT = Token(powerf);
			break;

		default:
			newT = Token(0.0f);
			break;
		}

		

		
	} else {

		int i1 = getTokenInt(n1);
		int i2 = getTokenInt(n2);

		switch (arithmeticOperator) {

		case '+':
			newT = Token(i1 + i2);
			break;

		case '-':
			newT = Token(i1 - i2);
			break;

		case '*':
			newT = Token(i1 * i2);
			break;

		case '/':

			newT = Token(i1 / i2);
			break;

		case '%':
			modulus = i1 % i2;
			newT = Token(i1 % i2);
			break;

		case '^':
			power = pow(i1, i2);
			newT = Token(power);
			break;

		default:
			newT = Token(0.0f);
			break;

		}

	}

	return newT;
}

void InfixToPostFixConverter::printStackBeauty(std::vector<Token> stacky)
{
	string str = "";

	if (stacky.empty()) {
		cout << "\t\t\tVacia!" << endl;
		return;
	}

	for (auto t : boost::adaptors::reverse(stacky)) {

		string newStr;
		newStr.push_back(getTokenChar(t));

		str += "\t\t\t|              |\n";
		str += "\t\t\t|              |\n";
		str += "\t\t\t|              |\n";
		str += "\t\t\t|        "+newStr+"     |\n";
		str += "\t\t\t|              |\n";
		str += "\t\t\t|______________|\n";
	}

	cout << str << endl;
}

void InfixToPostFixConverter::convertInfixToPostFix()
{

	tokenizeInfixString(); 

	if (semanticError == true) {
		return;
	}


	/* Following the algorithm mention here: https://www.includehelp.com/c/infix-to-postfix-conversion-using-stack-with-c-program.aspx */
	// Actual helpfull algorithm: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/

	vector<Token> stacky;


	/* Add parenthesis to the entire expression */
	stacky.push_back(Token('(')); 
	tokens.push_back(Token(')'));

	for (Token t : tokens) {

		printToken(t);

		if (t.getType() == "int") { 

			postFix += to_string(getTokenInt(t));
			postFix += ",";
			postFixVector.push_back(t);
		}  else if (t.getType() == "float") {

			postFix += to_string(getTokenFloat(t));
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
					postFixVector.push_back(postFix.back());
					postFix += ",";
			
					stacky.pop_back();
				}

				
				stacky.pop_back(); //Remove parenthesis

			} else if (t.to_string() == "]") {

				while (getTokenChar(stacky.back()) != '[') {

					string popItem;
					postFix.push_back(getTokenChar(stacky.back()));
					postFixVector.push_back(postFix.back());
					postFix += ",";
					stacky.pop_back();
				}

				stacky.pop_back(); //Remove curly bracket

			} else {

				// 4^2*3-3+8/4/(1+1)

				/*.3.1 If the precedence of the scanned operator is greater than the precedence
				of the operator in the stack(or the stack is empty or the stack contains a ‘(‘), push it.
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
		printStackBeauty(stacky);

	}

	evaluatePostFix();
  
	/*cout << postFix << endl;*/
}

void InfixToPostFixConverter::tokenizeInfixString()
{	
	vector<string> untokenize;
	string variablesTypesFoundFromInput;
	std::regex words_regex("[0-9]?([0-9]*[.])?[0-9]+|[\\%\\[\\]\\^\\-\\+\\\\\(\\)\\/\\*]"); 
	auto words_begin = std::sregex_iterator(infix.begin(), infix.end(), words_regex);
	auto words_end = std::sregex_iterator();

	/* Separate every int or float or operator from the infix input into a single string using regular expression and store it in the vector untokenize */

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		untokenize.push_back((*i).str());
	}

	variablesTypesFoundFromInput = "Tipos encontrados: ";

	/* Populate the tokens vector */

	for (string str : untokenize) {

		Token newToken;

		if (str.find('.') != string::npos) { // Checking to see if its a floating number by seeing if the current string has a char equal to '.' 

			float n = boost::lexical_cast<float>(str);
			newToken = Token(n);
			variablesTypesFoundFromInput += "Flotante ";

		} else if (Parser::isValidOperand(str[0])) { //Checking if its a operator

			newToken = Token(str[0]);
			variablesTypesFoundFromInput += "Operador" + str + " ";

		} else { //Its a int

			int n = boost::lexical_cast<int>(str);
			newToken = Token(n);
			variablesTypesFoundFromInput += "Entero ";

		}

		tokens.push_back(newToken);
	}

	Parser::printColoredMessage(variablesTypesFoundFromInput, 14); //Print the variables types in yellow

	/* Check to see if there are more validation errors in the infix input */

	for (int i = 0; i < untokenize.size(); i++) {

		if (i == 0 || i == (untokenize.size() - 1)) {

			/* Check if the input has only this two cases -> (.) or [.], if true, mark it as error */

			if (untokenize.size() == 2 && untokenize[0][0] == '(' && untokenize[1][0] == ')') {
				this->errorMessage = "Error Letal: Se ha encontrado un \".\" por si solo, lo cual no es valido, debe de ir acompañado de un digito ";
				semanticError = true;
				return;
			} 
			
			if (untokenize.size() == 2 && untokenize[0][0] == '[' && untokenize[1][0] == ']') {
				this->errorMessage = "Error Letal: Se ha encontrado un \".\" por si solo, lo cual no es valido, debe de ir acompañado de un digito ";
				semanticError = true;
				return;
			}

			continue;
		}
			

		switch (untokenize[i][0]) {

		case '(': case '[':

			/* If a left parenthesis or curly bracket is found, then check the character before it isnt a digit */
			/* If it is a digit, then it shouldnt be allowed to do so, example: 4(4) -> Wrong, it should be: 4*(4) */
			if (isdigit(untokenize[i - 1][0])) {

				this->errorMessage = "Error: Un digito que esta seguido de un parentesis o corchete se ha encontrado (esto es invalido, debe especificar un operador)\nEjemplo: 4(4) -> Incorrecto, Valido: 4*(4)";
				semanticError = true;
				return;
			}

			/* If a left parenthesis is found and the next character is a right parenthesis, then this means that its an empty parenthesis () */
			if (untokenize[i + 1][0] == ')') {
				
				this->errorMessage = "Error: Un parentesis vacio se ha encontrado";
				semanticError = true;
				return;
			}

			/* If a left curly bracket is found and the next character is a right curly bracket, then this means that its an empty parenthesis () */
			if (untokenize[i + 1][0] == ']') {

				this->errorMessage = "Error: Un corchete vacio se ha encontrado";
				semanticError = true;
				return;
			}

			break;

			/* If a right parenthesis or curly bracket is found, then check the character after it isnt a digit */
			/* If it is a digit, then it shouldnt be allowed to do so, example: (4)4 -> Wrong, it should be: (4)*4 */
		case ')': case ']':
			if (isdigit(untokenize[i + 1][0])) {
				this->errorMessage = "Error semantico: Un parentesis o corchete que esta seguido de un digito se ha encontrado(esto es invalido, debe especificar un operador)\nEjemplo: (4)4 -> Incorrecto, Valido: (4)*4";
				semanticError = true;
				return;
			}
			break;

		/*case '.':
			this->errorMessage = "Error Letal: Se ha encontrado un \".\" por si solo, lo cual no es valido, debe de ir acompañado de un digito ";
			semanticError = true;
			return;
			break;*/

		}

	}


	semanticError = false;
}


//TODO:
//Para finalizar las validaciones, en el vector untokenize, ahi se puede verificar las ultimas condiciones
// ejemplo -> (3) MALO! 4+(4)