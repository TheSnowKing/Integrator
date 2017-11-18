/**
 *  Author: Conor Poland
 */

#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <vector>
#include <functional>
#include <cassert>

enum QuadratureRule
{
	FORWARD_EULER,
//	BACKWARD_EULER
//	TRAPEZOIDAL,
//	LEAP_FROG
//	RUNGE_KUTTA
};

class Integral
{
public:
	/* Constructor */
	Integral(QuadratureRule r) : rule(r) {}
	
	/* Compute the time-h flow for a function defined by f */

	// For generic functions
	double flow(std::function<double(double)> f, double y_0, double h);

	// For calculated derivatives f
	double flow(double f, double y_0, double h);

	// For calculated gradients f
	std::vector<double> flow(std::vector<double> f, std::vector<double> y_0, double h);


	/* Setter */
	void set(QuadratureRule rule) {
		this->rule = rule;
	}

private:
	QuadratureRule rule;
};

#endif // INTEGRAL_H
