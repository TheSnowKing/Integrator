/**
 *  Author: Conor Poland
 */

#include <iostream>
#include "Integral.h"

/* Compute the time-h flow for a function defined by f */
double Integral::flow(std::function<double(double)> f, double y_0, double h)
{
	double y_1;

	switch (rule) {
	case FORWARD_EULER:
		y_1 = y_0 + h*f(y_0);
		break;
/*
	case BACKWARD_EULER:

		break;

	case TRAPEZOIDAL:
		break;

	case LEAP_FROG:
		break;
*/
	}

	return y_1;
}

/* Compute the time-h flow for a function defined by f */
double Integral::flow(double f, double y_0, double h)
{
	double y_1;

	switch (rule) {
	case FORWARD_EULER:
		y_1 = y_0 + h*f;
		break;
/*
	case BACKWARD_EULER:

		break;

	case TRAPEZOIDAL:
		break;

	case LEAP_FROG:
		break;
*/
	}

	return y_1;

}

std::vector<double> Integral::flow(std::vector<double> f, std::vector<double> y_0, double h)
{
	assert(f.size() == y_0.size());

	int size = f.size();
	std::vector<double> y_1(size, 0);	// Return vector

	switch (rule) {
	case FORWARD_EULER:
		for (int i = 0; i < size; i++) {
			y_1[i] = y_0[i] + h*f[i];

		}
		break;
/*
	case BACKWARD_EULER:

		break;

	case TRAPEZOIDAL:
		break;

	case LEAP_FROG:
		break;
*/
	}

	return y_1;

}
