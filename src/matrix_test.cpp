//#include "catch.hpp"
#include "matrix.h"

#include <iostream>
#include <vector>

//#define CATCH_CONFIG_MAIN



//SCENARIO("Matrix build works") {
int main() {

  std::vector<std::vector<double>> vec{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Matrix m{vec};

  std::cout << "Original matrix:" << std::endl;

  std::cout << m << std::endl;

  std::cout << "Transposed:" << std::endl;

  std::cout << m.transpose() << std::endl;

  std::cout << "Original multiplied by transposed:" << std::endl;

  std::cout << m * m.transpose() << std::endl;

  std::cout << "Determinant of matrix:" << std::endl;

  std::cout << m.determinant() << std::endl;

  std::cout << "Raise to the power of 10:" << std::endl;

  std::cout << (m^10) << std::endl;

  std::cout << "New Matrix:" << std::endl;

  std::vector<std::vector<double>> vec2{{6, 1, 1}, {4, -2, 5}, {2, 8, 7}};

  Matrix m2{vec2};

  std::cout << m2 << std::endl;

  std::cout << "Determinant:" << std::endl;

  std::cout << m2.determinant() << std::endl;
 
  std::cout << "Determinant minors:" << std::endl;

  std::cout << m2.takeMinor(0, 0) << std::endl;
  std::cout << m2.takeMinor(0, 1) << std::endl;
  std::cout << m2.takeMinor(0, 2) << std::endl;

  std::cout << "Inverse:" << std::endl;
  
  std::cout << m2.invert() << std::endl;

  std::cout << "Regression:" << std::endl;

  std::vector<std::vector<double>> xvec{{1, 7, 4, 9, 2}, {1, 4, 9, 8, 0 }, {1, 9, 4, 2, 3}, {1, 3, 4, 5, 9}, {1, 6, 0, 2, 3}, {1, 1, 3, 2, 0}, {1, 0, 9, 9, 3}}; 
  std::vector<std::vector<double>> yvec{{10}, {3}, {7}, {4}, {12}, {1}, {9}};

  Matrix x{xvec};
  Matrix y{yvec};

  std::cout << "\tX:" << std::endl;

  std::cout << x << std::endl;

  std::cout << "\tY:" << std::endl;

  std::cout << y << std::endl;

  std::cout << "X'Y" << std::endl;

  std::cout << x.transpose() * y << std::endl;

  std::cout << "X'X" << std::endl;

  std::cout << x.transpose() * x << std::endl;
  
  std::cout << "Det" <<std::endl;

  std::cout << (x.transpose() * x).determinant() << std::endl;

  std::cout << "Inverse X'X" << std::endl;

  std::cout << (x.transpose() * x).invert() << std::endl;

  std::cout << "Betas:" << std::endl;

  std::cout << (x.transpose() * x).invert() * (x.transpose() * y) << std::endl;

  std::cout << "Xb" << std::endl;

  std::cout << x * ((x.transpose() * x).invert() * (x.transpose() * y)) << std::endl;

  std::cout << "Adding a row to X" << std::endl;

  std::vector<double> row{1, 0, 4, 3, 4};
  x.addRow(row);
  std::cout << x << std::endl;

}
