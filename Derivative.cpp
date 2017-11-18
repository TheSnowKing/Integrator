/**
 *  Author: Conor Poland
 */

#include "Derivative.h"

/* Evaluate the derivative for a given scalar value function f */
double Derivative::evaluate(std::function<double(double)> f, double x, double h)
{
	return (f(x + h) - f(x - h))/(2.0*h); 
}

/* Evaluate the derivative for a given vector value function f */
std::vector<double> Derivative::evaluate(std::function<double(std::vector<double>)> f, std::vector<double> x, double h)
{
	int size = x.size();
	std::vector<double> gradient(size, 0);

	// "Increment vectors"
	std::vector<double> x__(size, 0);	// Used to store x + 2h
	std::vector<double> x_(size, 0);	// Used to store x + h
	std::vector<double> _x(size, 0);	// Used to store x - h
	std::vector<double> __x (size, 0);	// Used to store x - 2h

	/*
	 *	FIRST METHOD - Better way
	 */

	// Loop over the dimension of the vector x
	for (int i = 0; i < size; i++) {

		// Reset the increment vectors to the initial vector x
		for (int j = 0; j < size; j++) {
			x__[j] = x[j];
			x_[j] = x[j];
			_x[j] = x[j];
			__x[j] = x[j];
		}

		// Modify the i'th component of the increment vectors
		x__[i] = x[i] + 2*h;
		x_[i] = x[i] + h;
		_x[i] = x[i] - h;
		__x[i] = x[i] - 2*h;
		// Calculate partial derivative ( -f(x+2h) + 8*f(x+h) - 8*f(x-h) + f(x-2h) )/12*h for component i
		gradient[i] = ( -f(x__) + 8*f(x_) - 8*f(_x) + f(__x) )/(12*h);
	}

	/*
	 *	SECOND METHOD - Simple way
	 */

/*
	// Loop over the dimension of the vector x
	for (int i = 0; i < size; i++) {

		// Reset the increment vectors to the initial vector x
		for (int j = 0; j < size; j++) {
			x_[j] = x[j];
			_x[j] = x[j];
		}

		// Modify the i'th component of the increment vectors
		x_[i] = x[i] + h;
		_x[i] = x[i] - h;
		// Calculate partial derivative (f(x+h) - f(x-h))/2*h for component i
		gradient[i] = (f(x_) - f(_x))/(2.0*h);
	}
*/
	return gradient;
}

