#include "catch.hpp"
#include "matrix.h"

#include <iostream>
#include <vector>

#define CATCH_CONFIG_MAIN



SCENARIO("Matrix build works") {
  std::vector<std::vector<double>> vec{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Matrix m{vec};

  std::cout << m << std::endl;

  /*REQUIRE(m[1][1] == 5);
  REQUIRE(m[2][1] == 8);
  REQUIRE(m[1][2] == 3);
  REQUIRE(m[1][0] == 4);
  REQUIRE(m[0][1] == 1);
  */

}


