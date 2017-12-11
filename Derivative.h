/**
 *  Author: Conor Poland
 */

#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include <vector>
#include <functional>
#include <iostream>
#include "Particle.h"

//template <class T>
class Derivative
{
public:
	/* Evaluate the derivative for a given scalar value function f */
	static double evaluate(std::function<double(double)> f, double x, double h);

	/* Evaluate the derivative for a given vector value function f */
	static std::vector<double> evaluate(std::function<double(std::vector<double>)> f, std::vector<double> x, double h); // FOR KINETIC ENERGY

	/* Evaluate the derivative for a given vector value function f */
//	static std::vector<double> evaluate(std::function<double(std::vector<double>, T*)> f, T* other, std::vector<double> x, double h); // FOR POTENTIAL ENERGY
	static std::vector<double> evaluate(std::function<double(std::vector<double>, Particle*)> f, Particle* other, std::vector<double> x, double h); // FOR POTENTIAL ENERGY


};

#endif // DERIVATIVE_H
