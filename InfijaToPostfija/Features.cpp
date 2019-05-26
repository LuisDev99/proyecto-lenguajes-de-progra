
/* 


	Features Usadas en el proyecto

	C++11: 

	1. Syntaxis de inicializacion
	Parser parser{ input }; // C++11 Inicializador con { }  -> Ubicacion: en el main.cpp
	Parser parser(input);

	2. Deduccion dinamica de tipo de variable
	auto leftOperandCounter = 0;  -> Ubicacion: en el parser.cpp
	auto rightOperandCounter = 0; -> Ubicacion: en el parser.cpp
	a

	3. Expressiones lambda 
	auto counter = [](string _input, char operand) {

		int operand_counter = 0;

		for (char inputchar : _input) {

			if (inputchar == operand)
				operand_counter++;

		}

		return operand_counter;
	}; -> Ubicacion: Parser.cpp

	4. nullptr
	int operand_counter = (int)nullptr; -> Ubicacion: Parser.cpp



	C++ 14:

	1. auto return type

	KeyGenerator () -> Ubicacion:  en InfixToPostFixConverter.cpp

	2. Generic Lambdas
	auto counter = [](string _input, char operand) { // C++ 11 CON C++14

		int operand_counter = (int)nullptr; //C++ 11

		for (char inputchar : _input) {

			if (inputchar == operand)
				operand_counter++;

		}

		return operand_counter;
	};


	3. Strongly type enums

	enum struct Priority -> Ubicacion: Parser.h

	4. Palabra reservada default

	Token() = default; Ubicacion -> InfixToPostFixConverter.h

	5. In class initialization

	private:
		any value;
		std::string strValue = "";
		int priority = 0; Ubicacion -> InfixToPostFixConverter.h

	Si lo hicieramos esto mismo anterior en c++ 11 se quejaria el compilador



	c++ 17

	1. objeto any -> Ubicacion: InfixToPostFixConverter.h
	2. boost lexical_cast -> Ubicacion: InfixToPostFixConverter.cpp
	3. any any_cast -> el mismo archivo
	4. boost range for each -> Ubicacion: InfixToPostFixConverter.cpp,  https://www.boost.org/doc/libs/1_68_0/libs/range/doc/html/index.html




*/