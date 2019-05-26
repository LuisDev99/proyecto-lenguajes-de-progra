#pragma once

#include <string>
#include <iostream>
#include "Parser.h"

using namespace std;

class Test {

public:

	static void TestAllCases() {

		int testsPassed = 0;

		if (assert("1+1", "2", false)) { //Se espera que el resultado sea 2
			testsPassed++;
		}

		if (assert("1++1", "2", true)) { //Se espera que falle el test por la mala notacion infija
			testsPassed++;
		}

		if (assert("[]", "2", true)) { //Se espera que falle el test por la mala notacion infija
			testsPassed++;
		}

		if (assert("((", "2", true)) { //Se espera que falle el test por error de parentesis incompleto
			testsPassed++;
		}

		if (assert("[[", "2", true)) { //Se espera que falle el test por error de corchetes incompleto
			testsPassed++;
		}

		if (assert("a", "2", true)) { //Se espera que falle el test por error de caracter ilegal en la expresion
			testsPassed++;
		}

		if (assert("1+2*3", "7", false)) { //Se espera que el resultado sea 7
			testsPassed++;
		}

		system("cls");

		string msg = "Cantidad de Test Pasados: " + to_string(testsPassed) + " de 7";
		Parser::printColoredMessage(msg, 3);

		//cout << "Cantidad de Test Pasados: " << testsPassed << " de 7" << endl;
	}


	static bool assert(string input, string expectedOutput, bool expectedToFail) {

		Parser parser{ input };

		if (expectedToFail) {

			if (parser.didErrorOccurred())
				return true;
			else
				return false;

		}

		return expectedOutput == parser.getResult();

	}



};