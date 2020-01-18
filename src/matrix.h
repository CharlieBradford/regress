#ifndef SRC_REGRESS_H_
#define SRC_REGRESS_H_

#include <string>
#include <vector>



class Matrix {
  private:
    std::vector<std::vector<double> > values_;


  public:
      explicit Matrix(std::vector<std::vector<double> > values) : values_(values) {}
      Matrix(const Matrix& m) : values_(m.values_) {}
      Matrix(int height, int width);

      Matrix& operator=(const Matrix& m) noexcept;

      std::size_t length() const {
        return values_.size();
      }
      
      std::size_t height() const {
        return values_[0].size();
      }

      void addRow(std::vector<double> row);
      void addCol(std::vector<double> col);

      Matrix invert() const;
      Matrix transpose() const;
      Matrix takeMinor(std::size_t i, std::size_t j) const;
      Matrix diagonal() const;
      double determinant() const;

      std::vector<double>& operator[](const int& i);
      std::vector<double> operator[](const int& i) const;

      friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
      friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
      friend Matrix operator*(const double& lhs, const Matrix& rhs);
      friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
      friend Matrix operator/(const Matrix& lhs, const Matrix& rhs);
      friend Matrix operator^(const Matrix& lhs, const int& pow);

      friend std::ostream& operator<<(std::ostream& os, const Matrix& m);


};

/*
class MatrixError: public std::exception
{
  public:
    explicit MatrixError(const std::string& what) : what_(what) {}
    const char* what() const noexcept { return what_.c_str(); }

  private:
    std::string what_;
    


};
*/

#endif
