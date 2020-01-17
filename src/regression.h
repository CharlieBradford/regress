#ifndef

#include "src/matrix.h"

class Regression {
	private:
		Matrix x_;
		Matrix y_;
	public:
		Regression(Matrix x, Matrix y) : x_{x}, y_{y} {};
		virtual Matrix regress(Matrix x, Matrix y);
		virtual 
