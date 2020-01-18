#include "regression.h"

#include <boost.hpp>
#include <cmath>
#include <iostream>
#include <istream>


Matrix Regression::residuals() const {
  return y_ - x_ * regress();
}

Matrix Regression::variances() const {
  return ((ssr() / double(y_.length() - 1)) * (x_.transpose() * x_).invert()).diagonal();
}

Matrix Regression::t_stats() const {
  auto regression = regress();
  auto vars = variances();
  Matrix matrix{int(regression.length()), 1};
  for (std::size_t i = 0; i < regression.length(); ++i) {
    matrix[i][0] = regression[i][0] / sqrt(vars[i][0]);
  }
  return matrix;
}

void Regression::read(std::string filename) {
  std::ifstream file(filename);
  std::string line;

  while (getline(file, line)) {
    std::vector<std::string> vec;
    boost::algorithm::split(vec, line, boost::is_any_of(","));
  }

  
}

double Regression::ssr() const {
  return (residuals().transpose() * residuals())[0][0];
}

double Regression::sst() const {
  return (y_.transpose() * y_)[0][0];
}

double Regression::logLikelihood() const {
  return (y_.length()/-2) * std::log(2 * PI * ssr() / y_.length()) - 1/(2 * ssr() / y_.length())  * ssr();

}

double Regression::R2() const {
  return 1 - ssr()/sst();
}

Matrix InteractionRegression::regress() const {
  return (interaction_x_.transpose() * interaction_x_).invert() * (interaction_x_.transpose() * y_);
}

Matrix InteractionRegression::residuals() const {
  return y_ - interaction_x_ * regress();

}

Matrix InteractionRegression::variances() const {
  return ((ssr() / double(y_.length() - 1)) * (interaction_x_.transpose() * interaction_x_).invert()).diagonal();
}

Matrix InteractionRegression::regress(std::initializer_list<int> interactions) {
  reset();
  for (auto it = interactions.begin(); it != interactions.end(); ++it) {
    int i = *it;
    it++;
    if (it == interactions.end()) { continue; }
    int j = *it;

    addInteraction(i, j);
  }

  return (interaction_x_.transpose() * interaction_x_).invert() * (interaction_x_.transpose() * y_);
}

void InteractionRegression::addInteraction(int i, int j) {
  std::vector<double> interaction{};
  for (std::size_t k = 0; k < x_.length(); ++k)
    interaction.push_back(x_[k][i] * x_[k][j]);

  interaction_x_.addCol(interaction);
}

void InteractionRegression::setLog(int i) {
  for (std::size_t j = 0; j < x_.length(); ++j) 
    x_[j][i] = std::log(x_[j][i]);
}

