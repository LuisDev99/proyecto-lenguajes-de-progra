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

		if (assert("1+2*3", "7", false)) { //Se espera que el resultado sea 7
			testsPassed++;
		}

		cout << "Cantidad de Test Pasados: " << testsPassed << " de 3" << endl;
		
	}


	static bool assert(string input, string expectedOutput, bool expectToFail) {

		Parser parser{ input };

		if (expectToFail) {

			if (parser.didErrorOccurred())
				return true;
			else
				return false;

		}

		return expectedOutput == parser.getResult();

	}



};