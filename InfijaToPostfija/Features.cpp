
/* 


	Features Usadas en el proyecto

	C++11: 

	Syntaxis de inicializacion
	Parser parser{ input }; // C++11 Inicializador con { }  -> Ubicacion: en el main.cpp

	Deduccion dinamica de tipo de variable
	auto leftOperandCounter = 0;  -> Ubicacion: en el parser.cpp
	auto rightOperandCounter = 0; -> Ubicacion: en el parser.cpp

	Expressiones lambda 
	auto counter = [](string _input, char operand) {

		int operand_counter = 0;

		for (char inputchar : _input) {

			if (inputchar == operand)
				operand_counter++;

		}

		return operand_counter;
	}; -> Ubicacion: Parser.cpp

	nullptr
	int operand_counter = (int)nullptr; -> Ubicacion: Parser.cpp



	C++ 14:

	auto return type



	c++ 17

	objeto any -> Ubicacion: InfixToPostFixConverter.h
	boost lexical_cast -> Ubicacion: InfixToPostFixConverter.cpp
	any any_cast -> el mismo archivo
	boost range for each -> Ubicacion: InfixToPostFixConverter.cpp,  https://www.boost.org/doc/libs/1_68_0/libs/range/doc/html/index.html




*/