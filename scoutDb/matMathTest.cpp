
#include <cmath>

#include <iomanip>
#include <iostream>

//define MM_DEBUG to get detailed debug info (NOTE: can reduce performance compared to MM_TRACE)
//define MM_TRACE to get trace messages without altering the behavior of the matrix math

//NOTE: MM_DEBUG *WILL* change the output matrix if a matrix is not invertible

// #define MM_DEBUG
// #define MM_TRACE

#include "matMath.hpp"

using namespace std;

using namespace MatrixMath;

string input;

int main() {
  const size_t DIM           = 3;
  double *     testInput     = new double[DIM * DIM];
  double *     testOutput    = new double[DIM * DIM];
  double *     testAugmented = new double[DIM * DIM * 2];

  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      testInput[i * DIM + j]  = 2 * i + j + DIM;
      testOutput[i * DIM + j] = testAugmented[i * DIM * 2 + j] =
          testAugmented[i * DIM * 2 + DIM + j] = 0.;
    }
    testOutput[i * DIM + i] = 1.;
  }

  cout << "Test input:" << endl;

  printMtx(testInput, DIM);

  cout << endl << "Test output:" << endl;

  printMtx(testOutput, DIM);

  cout << endl << "Running inverter..." << endl;

  MatrixInverter inverter = MatrixInverter(testInput, DIM);

  double det = inverter.gaussElim();

  cout << endl << "Determinant: " << det << endl;

  cout << endl << "Output:" << endl;

  inverter.outputInverse(testOutput);

  printMtx(testOutput, DIM);

  cout << endl
       << "Transformed input (identity " << (MM_FZERO(det) ? "not " : "")
       << "expected):" << endl;

  inverter.outputIdent(testOutput);

  printMtx(testOutput, DIM);

  cout << endl << "Augmented matrix:" << endl;

  inverter.printAll(testAugmented);

  printMtx(testAugmented, DIM, DIM * 2);

  cout << endl << "Done." << endl;

  delete[] testInput;
  delete[] testOutput;
  delete[] testAugmented;

  return 0;
}
