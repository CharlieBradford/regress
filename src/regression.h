#ifndef src_regression_h
#define src_regression_h

#include "matrix.h"

#include <boost/format.hpp>
#include <initializer_list>
#include <iostream>

#define PI 3.1415

class Regression {
	protected:
		Matrix x_;
		Matrix y_;
    std::vector<std::string> labels_;
	public:
		Regression(Matrix x, Matrix y) : x_{x}, y_{y} {};
		Regression(Matrix x, Matrix y, std::vector<std::string> labels) : x_{x}, y_{y}, labels_{labels} {};

    friend std::ostream& operator<<(std::ostream& os, const Regression& r){
      auto reg = r.regress(), tst = r.t_stats();
      for (std::size_t i = 0; i < r.n_params(); ++i) {
        std::cout << boost::format("%10.4f\t(%10.4f)\n") % reg[i][0] % tst[i][0];
      }
      return os;
    }

    virtual Matrix regress() const {
      return (x_.transpose() * x_).invert() * (x_.transpose() * y_);
    }

    virtual Matrix residuals() const;
    virtual Matrix variances() const;
    Matrix t_stats() const;

    double ssr() const;
    double sst() const;
    
    double logLikelihood() const;
    double R2() const;
    double schwarz() const { return 0; }
    double akaike() const { return 0; }

    std::size_t n() const { return y_.length(); }
    virtual std::size_t n_params() const { return x_.height(); }

    void read(std::string);
};

class InteractionRegression : public Regression {
  private:
    Matrix interaction_x_;

  public:
    InteractionRegression(Matrix x, Matrix y) : Regression(x, y), interaction_x_{x} {};
    InteractionRegression(Matrix x, Matrix y, std::vector<std::string> labels) : Regression(x, y, labels), interaction_x_{x} {}
    Matrix regress() const;
    Matrix regress(std::initializer_list<int> interactions);

    Matrix residuals() const;
    Matrix variances() const;


    void addInteraction(int i, int j);
    void setLog(int i);
    void reset() { interaction_x_ = x_; }
    
    std::size_t n_params() const {return interaction_x_.height();}


    
};

class TimeSeriesRegression : public Regression {



};


#endif
