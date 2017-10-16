#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray*[r]) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new IntArray*[rhs.numRows])  {
  for (int i = 0; i < rhs.numRows; i++) {
    rows[i] = new IntArray(rhs.numColumns);
    *(rows[i]) = *(rhs.rows[i]);
  }

}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
     for (int i = numRows-1; i >= 0; i--) {
      delete rows[i];
    }
     //

    rows = new IntArray *[rhs.numRows];
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    for (int j = 0; j < numRows; j++) {
      rows[j] = new IntArray(numColumns);
      *(rows[j]) = *(rhs.rows[j]);
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows && index >= 0);
  return *(rows[index]);
}
IntArray & IntMatrix::operator[](int index){
  assert(index < numRows && index >= 0);
  return *(rows[index]);
}



bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(rhs.numRows == numRows);
  assert(rhs.numColumns == numColumns);
  IntMatrix sum(numRows, numColumns);
  
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {  
      sum[i][j] = rhs[i][j] + (*rows[i])[j];
    }
  }
  return sum;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  assert(rhs.getRows() >= 0);
  assert(rhs.getColumns() >= 0);
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << " \n";
    }
  }
  s << " ]";
  return s;
}
