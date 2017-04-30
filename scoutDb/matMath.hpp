#pragma once

#include <cassert>
#include <cmath>
#include <cstring>

#include <algorithm>
#include <iomanip>
#include <iostream>


// "using namespace" in a header is bad form, because then it adds that
// namespace to every .cpp file it's included in.

#define MM_EPSILON 1e-10

#define MM_FZERO(f) (fabs((f)) < MM_EPSILON)
#define MM_FEQUAL(f, g) MM_FZERO(f - g)
#define MM_FIXZERO(e, f)                                                       \
  {                                                                            \
    if (MM_FZERO(e)) f = 0.;                                                   \
  }

#ifdef MM_DEBUG
#define MM_TRACEMTX printMtx(arr, rows, cols)
#define MM_TRACE
#else
#define MM_TRACEMTX
#endif

namespace MatrixMath {
inline void printMtx(double *arr, size_t rows, size_t cols) {
  std::ios fmt(nullptr);
  fmt.copyfmt(std::cout);

  for (size_t r = 0; r < rows; ++r) {
    for (size_t c = 0; c < cols; ++c) {
      if (c) std::cout << (c == rows ? " | " : " ");

      double val = arr[r * cols + c], aval = fabs(val);

      std::cout << std::setw(10) << std::setfill(' ')
                << (aval >= 1e3 || aval <= 1e-2 && aval != 0. ?
                        std::scientific :
                        std::fixed)
                << std::setprecision(3) << arr[r * cols + c];
    }

    std::cout << std::endl;
  }

  std::cout.copyfmt(fmt);
}

inline void printMtx(double *arr, size_t dim) { printMtx(arr, dim, dim); }

class MatrixInverter {
  size_t  rows, cols;
  double *arr;

public:
  MatrixInverter(double *mat, size_t matSize)
      : rows(matSize), cols(matSize * 2) {
    arr = new double[rows * cols];

    for (size_t row = 0; row < matSize; ++row) {
      memcpy(arr + row * cols, mat + row * matSize, matSize * sizeof(double));

      for (size_t col = 0; col < matSize; ++col) {
        cell(row, rows + col) = col == row ? 1. : 0.;
      }
    }
  }

  ~MatrixInverter() { delete[] arr; }

private:
  inline double &cell(size_t row, size_t col) {
    assert(row < rows);
    assert(col < cols);
    return arr[row * cols + col];
  }

  void rowMult(size_t row, double fac) {
#ifdef MM_TRACE
    std::cout << "[Inverter] Multiplying row " << row << " by " << fac
              << std::endl;
#endif

#ifdef MM_DEBUG
    if (!MM_FEQUAL(fac, 1.)) {
#else
    if (MM_FEQUAL(fac, 1.)) return;
#endif

      for (size_t i = 0; i < cols; ++i)
        MM_FIXZERO(cell(row, i) *= fac, cell(row, i))

#ifdef MM_DEBUG
    }
#endif

    MM_TRACEMTX;
  }

  void rowAdd(size_t from, size_t to, double fac) {
#ifdef MM_TRACE
    std::cout << "[Inverter] Adding " << fac << " times row " << from
              << " to row " << to << std::endl;
#endif

#ifdef MM_DEBUG
    if (!MM_FZERO(fac)) {
#else
    if (MM_FZERO(fac)) return;
#endif

      for (size_t i = 0; i < cols; ++i)
        MM_FIXZERO(cell(to, i) += cell(from, i) * fac, cell(to, i))

#ifdef MM_DEBUG
    }
#endif

    MM_TRACEMTX;
  }

  void rowSwap(size_t a, size_t b) {
#ifdef MM_TRACE
    std::cout << "[Inverter] Swapping rows " << a << " and " << b << std::endl;
#endif

    for (size_t i = 0; i < cols; ++i) std::swap(cell(a, i), cell(b, i));

    MM_TRACEMTX;
  }

public:
  // Returns the determinant of the input matrix.  You're welcome.
  double gaussElim() {
    double det = 1;

    MM_TRACEMTX;

    for (size_t i = 0; i < rows; ++i) {
      if (MM_FZERO(cell(i, i))) { // To avoid a divide-by-zero
        size_t j = i + 1;

        while (j < rows && MM_FZERO(cell(j, i))) ++j;

        // Everything below us is zero.  Our work here is done.
        if (j == rows) {
#ifdef MM_DEBUG
          std::cout << "[Inverter] Skipping row/column " << i
                    << " due to zeroes." << std::endl;

          det = 0.;
          continue; // You could technically return here, since we know the
                    // matrix isn't invertible now, but we don't to get the full
                    // debug output.
#else
#ifdef MM_TRACE
          std::cout << "[Inverter] No pivot found in row/column " << i
                    << "; stopping" << std::endl;
#endif

          return 0.;    // The matrix isn't invertible.
#endif
        }

        det = -det;
        rowSwap(i, j);
      }

      det *= cell(i, i);
      rowMult(i, 1. / cell(i, i));

      for (size_t j = i + 1; j < rows; ++j) rowAdd(i, j, -cell(j, i));
    }

    for (size_t i = 0; i < rows; ++i) {
      size_t j = 0;

      while (j < rows && MM_FZERO(cell(i, j))) ++j;

#ifdef MM_DEBUG
      if (j == rows) {
        std::cout << "[Inverter] No pivot in row " << i << std::endl;

        continue;
      }
#else
      assert(j < rows); // We should've already stopped if a pivot is missing.
#endif

      assert(j >= i);
      assert(MM_FEQUAL(cell(i, j), 1.));

      if (j == rows) continue;

      for (size_t k = 0; k < i; ++k) { rowAdd(i, k, -cell(k, j)); }
    }

    return det;
  }

  void outputIdent(double *output) {
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < rows; ++j) {
        output[i * rows + j] = arr[i * cols + j];
      }
    }
  }

  void outputInverse(double *output) {
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < rows; ++j) {
        output[i * rows + j] = arr[i * cols + rows + j];
      }
    }
  }

  void printAll(double *output) {
    memcpy(output, arr, rows * cols * sizeof(double));
  }
};
}
