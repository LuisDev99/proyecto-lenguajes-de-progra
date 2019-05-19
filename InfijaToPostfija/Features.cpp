
/* 


	Features Usadas en el proyecto

	C++11: 

	1. Syntaxis de inicializacion
	Parser parser{ input }; // C++11 Inicializador con { }  -> Ubicacion: en el main.cpp

	2. Deduccion dinamica de tipo de variable
	auto leftOperandCounter = 0;  -> Ubicacion: en el parser.cpp
	auto rightOperandCounter = 0; -> Ubicacion: en el parser.cpp

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





	c++ 17

	1. objeto any -> Ubicacion: InfixToPostFixConverter.h
	2. boost lexical_cast -> Ubicacion: InfixToPostFixConverter.cpp
	3. any any_cast -> el mismo archivo
	4. boost range for each -> Ubicacion: InfixToPostFixConverter.cpp,  https://www.boost.org/doc/libs/1_68_0/libs/range/doc/html/index.html




*/