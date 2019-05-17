#include <iostream>
#include <sstream>
#include <string>
#include "Parser.h"


using namespace std;


void main() {

	int menu = 0;
	string input= " ", output = " ";
	
	do {
		
		cout << " \n\t*** INFIX TO POSTFIX TOOL *** \n\n";

		cout << "Ingrese la notacion infija: ";
		cin >> input;

		cout << " \n\t\t ============= Procedimiento ==================\n\n";

		Parser parser{ input }; // C++11 Inicializador con { }

		output = parser.getResult();

		cout << output <<endl;

		cout << " \n\t\t =============      Fin      ==================\n\n";

	
	} while (menu != 2);

	return;
}