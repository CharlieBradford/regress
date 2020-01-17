#include "./matrix.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
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

void Matrix::addRow(std::vector<double> row) {
	if (row.size() != height())
		throw std::runtime_error("Row mismatched with vector");
	values_.push_back(row);
}

void Matrix::addCol(std::vector<double> col) {
	if (col.size() != length())
		throw std::runtime_error("Column mismatched with vector");
	for (std::size_t i = 0; i < height(); ++i) 
		values_[i].push_back(col[i]);
}

Matrix Matrix::invert() const {
	auto det = (*this).determinant();
	if (det == 0) {
		throw std::runtime_error("Can't find inverse; determinant = 0");
	} else if (length() != height()) {
		throw std::runtime_error("Can't find inverse of non-square matrix");
	}

	auto neg = 1;
	Matrix matrix(length(), height());
	for (std::size_t i = 0; i < length(); ++i) {
		for (std::size_t j = 0; j < height(); ++j) {
			matrix[i][j] = neg * (1/det) * takeMinor(i, j).determinant();
			neg *= -1;
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

Matrix Matrix::takeMinor(std::size_t i, std::size_t j) const{
	if (i >= length() || j >= height()) {
		throw std::runtime_error("Parameters too large to form takeMinor matrix"); 
	}

	int addOnX = 0, addOnY = 0;

	Matrix matrix(length()-1, height()-1);
	for (std::size_t x = 0; x < length()-1; ++x) {
		if (x == i) { addOnX = 1; }
		addOnY = 0;
		for (std::size_t y = 0; y < height()-1; ++y) {
			if (y == j) { addOnY = 1; }
			matrix[x][y] = values_[x+addOnX][y+addOnY];
		}
	}
	return matrix;

}

double Matrix::determinant() const {
	if (length() != height()) {
		throw std::runtime_error("Determinant only calculable for square matrices");

	}
	if (length() == 2) {
		return (*this)[0][0]*(*this)[1][1] - (*this)[0][1]*(*this)[1][0];

	}

	double det = 0;
	for (std::size_t i = 0; i < length(); ++i) {
		det += (i % 2 == 0 ? 1 : -1) * (*this)[0][i] * (*this).takeMinor(0, i).determinant();
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
		throw std::runtime_error("Matrices don't have matching dimensions.");
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
		throw std::runtime_error("Matrices don't have matching dimensions.");

	}

	Matrix matrix(lhs.length(), rhs.height());
	for (std::size_t i = 0; i < lhs.length(); ++i) {
		for (std::size_t j = 0; j < rhs.height(); ++j) {
			for (std::size_t k = 0; k < rhs.length(); ++k) {
				matrix[i][j] += (lhs[i][k] * rhs[k][j]);
//				std::cout << "Point: " << i << ", " << j << " = " << matrix[i][j] << std::endl;
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

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	for (std::size_t i = 0; i < m.length(); ++i) {
		for (std::size_t j = 0; j < m.height(); ++j) {
			os << std::setw(5) << std::setprecision(5) << m[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}
