#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T>** rows;
 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix<T> & rhs);
  ~Matrix();
  Matrix<T> & operator=(const Matrix<T> & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;
};

///////////methods implementation
template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0) {
}

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T>*[r]) {
  for (int i = 0; i < r; i++) {
    rows[i] = new std::vector<T>(c);
    //*(rows[i]).reserve(c);
  }
}
template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new std::vector<T>*[rhs.numRows])  {
  for (int i = 0; i < rhs.numRows; i++) {
    rows[i] = new std::vector<T>(rhs.numColumns);
    *(rows[i]) = *(rhs.rows[i]);
  }
}
template<typename T>
Matrix<T>::~Matrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  if (this != &rhs) {
    for (int i = numRows-1; i >= 0; i--) {
      delete rows[i];
    }
    //

    rows = new std::vector<T>*[rhs.numRows];
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    for (int j = 0; j < numRows; j++) {
      rows[j] = new std::vector<T>(rhs.numColumns);
      *(rows[j]) = *(rhs.rows[j]);
    }
  }
  return *this;
}
  
template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}
template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}
template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(index < numRows && index >= 0);
  return *(rows[index]);
}
template<typename T>
std::vector<T> & Matrix<T>::operator[](int index){
  assert(index < numRows && index >= 0);
  return *(rows[index]);
}


template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (rhs.numRows != numRows || rhs.numColumns != numColumns) {
    return 0;
  }
  else {
    for (int i = 0; i < numRows; i++) {
      if (*(rows[i]) != *(rhs.rows[i])) {
	return 0;
      }
    }
  }
  return 1;
}
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(rhs.numRows == numRows);
  assert(rhs.numColumns == numColumns);
  Matrix<T> sum(numRows, numColumns);

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      sum[i][j] =  (*rows[i])[j] + rhs[i][j];
    }
  }
  return sum;
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  assert(rhs.getRows() >= 0);
  assert(rhs.getColumns() >= 0);
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << "{";
    for (int j = 0; j < rhs.getColumns(); j++) {
      s << rhs[i][j];
      if (j != rhs.getColumns() - 1) {
	s << ", ";
      }
    }
    s<< "}";
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
#endif
