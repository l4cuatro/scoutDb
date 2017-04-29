#include <iostream>

#include "matMath.hpp"

using namespace std;

using namespace MatrixMath;

double* testInput;
double* testOutput;

string input;

int main() {

	testInput = (double*)(malloc(9 * sizeof(double)));
	testOutput = (double*)(malloc(9 * sizeof(double)));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			testInput[i * 3 + j] = 2 * i + j + 3;
			testOutput[i * 3 + j] = 0;
		}
		testOutput[i * 3 + i] = 1;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << *(testInput + i * 3 + j);
			cout << (j == 2)
				? "/n"
				: ", ";
		}
	}

	cout << "\n\n\n\n\n";

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << testOutput[i * 3 + j] << ", ";
		}
		cout << "\n";
	}

	cout << "\n\n\n\n\n\n\n\n\n\n\n";

	MatrixInverter MatInvert = MatrixInverter(testInput, 3);

	MatInvert.gaussElim();

	MatInvert.outputInverse(testOutput);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << testOutput[i * 3 + j] << ", ";
		}
		cout << "\n";
	}

	cout << "\n\n\n\n\n";

	MatInvert.outputIdent(testOutput);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << testOutput[i * 3 + j] << ", ";
		}
		cout << "\n";
	}


	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	cout << "Augmented matrix: \n";

	MatInvert.printAll();

	cout << "\nEnd of Program\n";

	return 0;

}
