#include "regress.h"

#include <algorithm>
#include <boost>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

Matrix::Matrix(int i, int j)
{
  values_ = std::vector<std::vector<double> >();
  
  for (auto x = 0; x < i; ++x) {
    std::vector<double> tmp(j, 0.0);
    values_.push_back(tmp);
  }

}

Matrix& Matrix::operator=(const Matrix& m) noexcept {
  values_ = m.values_;
  return *this;
}

Matrix Matrix::invert() const {
  auto det = (*this).determinant();
  if (det == 0) {
    throw MatrixError("Can't find inverse; determinant = 0");
  } else if (length() != height()) {
    throw MatrixError("Can't find inverse of non-square matrix");
  }

  Matrix matrix(length(), height());
  for (std::size_t i = 0; i < length(); ++i) {
    for (std::size_t j = 0; j < height(); ++j) {
      matrix[i][j] = (1/det) * minor(i, j).determinant();
    }
  }
  return matrix;
}

Matrix Matrix::transpose() const {
  Matrix matrix(height(), length());
  for (std::size_t i = 0; i < length(); ++i) {
    for (std::size_t j = 0; j < height(); ++j) {
      matrix[j][i] = (*this)[i][j];
    }
  }
  return matrix;
}

Matrix Matrix::minor(std::size_t i, std::size_t j) const{
  if (i >= length() || j >= height()) {
    throw MatrixError("Parameters too large to form minor matrix"); 
  }

  int addOnX = 0, addOnY = 0;

  Matrix matrix(length()-1, height()-1);
  for (std::size_t x = 0; x < length()-1; ++x) {
    if (x == i) { addOnX = 1; continue; }
    for (std::size_t y = 0; y < height()-1; ++y) {
      if (y == i) { addOnY = 1; continue; }
      matrix[x][y] = values_[x+addOnX][y+addOnY];
    }
  }
  return matrix;

}

double Matrix::determinant() const {
  if (length() != height()) {
    throw MatrixError("Determinant only calculable for square matrices");

  }
  if (length() == 2) {
    return (*this)[0][0]*(*this)[1][1] - (*this)[0][1]*(*this)[1][0];

  }

  double det = 0;
  for (std::size_t i = 0; i < length(); ++i) {
    det += (i % 2 ? 1 : -1) * (*this)[1][i] * (*this).minor(i, i).determinant();
  }
  return det;
}




std::vector<double>& Matrix::operator[](const int& i) {
  return values_[i];
} 

std::vector<double> Matrix::operator[](const int& i) const { 
  return values_[i];
}


Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
  if (lhs.length() != rhs.length() || lhs.height() != rhs.height()) {
    throw MatrixError("Matrices don't have matching dimensions.");
  }
  Matrix matrix = lhs;
  for (std::size_t i = 0; i < lhs.length(); ++i) {
    for (std::size_t j = 0; j < lhs.height(); ++j) {
      matrix[i][j] += rhs[i][j];
    }
  }
  return matrix;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
  if (lhs.height() != rhs.length()) {
    throw MatrixError("Matrices don't have matching dimensions.");
  }

  Matrix matrix(lhs.length(), rhs.height());
  for (std::size_t i = 0; i < lhs.length(); ++i) {
    for (std::size_t j = 0; j < rhs.height(); ++j) {
      for (std::size_t k = 0; k < rhs.length(); ++k) {
        matrix[i][j] += lhs[i][k] * rhs[k][j];
      }
    }
  }

  return matrix;
}

Matrix operator/(const Matrix& lhs, const Matrix& rhs) {
  return lhs * rhs.invert();
}

Matrix operator^(const Matrix& lhs, const int& pow) {
  if (pow > 0) {
    return pow > 1 ? lhs * (lhs ^ (pow - 1)) : lhs;
  } else {
    return lhs.invert() ^ -pow;
  }
}

Matrix operator<<(std::ostream& os, const Matrix& m) {
  for (std::size_t i = 0; i < m.length(); ++i) {
    for (std::size_t j = 0; j < m.height(); ++j) {
      os << boost::format("%5.2f ", m[i][j]);
    }
    os << "\n";
  }
}
