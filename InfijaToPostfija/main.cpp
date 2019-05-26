#include <iostream>
#include <sstream>
#include <string>
#include "Parser.h"
#include <Windows.h>
#include "Test.h"

#define RED 12
#define GREEN 10
#define BLUE 9

using namespace std;


void main() {

	int menu = 0;
	string input= " ", output = " ";

	Test::TestAllCases();
	
	do {
		
		cout << " \n\t*** INFIX TO POSTFIX TOOL *** \n\n";

		cout << "Ingrese la notacion infija: ";
		cin >> input;

		cout << " \n\t\t ============= Procedimiento ==================\n\n";

		if (input == "()" || input == "[]" || input == ".") {//Very special case that saves a lot of lifes
			cout << "Huh?? Intentando quebrar mi codigo??? ERROR! " << endl;
			continue;
		}

		Parser parser{ input }; // C++11 Inicializador con { }

		if (parser.didErrorOccurred()) {

			Parser::printColoredMessage(parser.getErrorMessage(), RED);

			cout << " \n\t\t =============  Hubo Fallo ==================\n\n";
			continue;
		}


		cout << "Resultado total postfijo: "; 
		Parser::printColoredMessage(parser.getPostFix(), GREEN);


		cout << "\nEl resultado es: ";
		Parser::printColoredMessage(parser.getResult(), BLUE);


		cout << " \n\t\t =============      Fin      ==================\n\n";

	
	} while (menu != 2);

	return;
}