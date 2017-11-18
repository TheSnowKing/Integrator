/**
 *  Author: Conor Poland
 */

#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include <vector>
#include <functional>
#include <iostream>
class Derivative
{
public:
	/* Evaluate the derivative for a given scalar value function f */
	static double evaluate(std::function<double(double)> f, double x, double h);

	/* Evaluate the derivative for a given vector value function f */
	static std::vector<double> evaluate(std::function<double(std::vector<double>)> f, std::vector<double> x, double h);
};

#endif // DERIVATIVE_H
