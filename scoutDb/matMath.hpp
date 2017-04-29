using namespace std;

namespace MatrixMath {
	
	class MatrixInverter {
		
		int matDims;

		double* arr;
		
	public: MatrixInverter(double* mat, int matSize) {
			
			matDims = matSize;
			
			arr = (double*)(malloc(2 * matDims * matDims * sizeof(double)));
			
		}
		
		void rowMult(double* arr, int row, double fac) {
			for(int i = 0; i < matDims * 2; i++) {
				if (arr[row * matDims + i] != 0)
					arr[row * matDims + i] *= fac;
				else
					arr[row * matDims + i] = 0;
			}
		}
		
		void rowAdd(double* arr, int row1, int row2, double fac) {
			for(int i = 0; i < matDims * 2; i++) {
				arr[row2 * matDims + i] += arr[row1 * matDims + i] * fac;
			}
		}
		
		public: void gaussElim() {
			for(int i = 0; i < matDims; i++) {
				rowMult(arr, i, pow(arr[i * matDims * 2 + i], -1));
				for(int j = 0; j < matDims; j++) {
					rowAdd(arr, j, i, -arr[j * matDims * 2 + i]);
				}
			}
		}
		
		public: void outputIdent(double* output) {
			for (int i = 0; i < matDims; i++) {
				for (int j = 0; j < matDims; j++) {
					output[i * matDims + j] = arr[i * matDims * 2 + j];
				}
			}
		}

		public: void outputInverse(double* output) {
			for(int i = 0; i < matDims * 2; i++) {
				for(int j = 0; j < matDims / 2; j++) {
					output[i * matDims + j] = arr[matDims + i * matDims * 2 + j];
				}
			}
		}

		public: void printAll() {
			for (int i = 0; i < matDims; i++) {
				for (int j = 0; j < matDims * 2; j++) {
					cout << arr[2 * matDims * i + j];
					cout << (j == matDims * 2 - 1)
						? "\n"
						: ", ";
				}
			}
		}
	};
}