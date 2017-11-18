/**
 *  Author: Conor Poland
 */

#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <functional>
#include "Integral.h"
#include "Derivative.h"
#include "util.h"

/* Function Prototypes */
void helpMessage();
void error(std::string message);
void processArgs(int argc, const char* argv[]);




class HarmonicOscillator
{
public:
	/* Constructor */
	HarmonicOscillator(double m, double k) {
		kinetic = T(m);
		potential = V(k);
	}

	/* Getters */
	// Return the kinetic energy function
	std::function<double(double)> getKinetic() const {
		return kinetic; 
	}

	// Return the potential energy function
	std::function<double(double)> getPotential() const {
		return potential;
	}

	// Return the kinetic energy evaluated at momentum p
	double getKinetic(double p) const {
		return kinetic(p); 
	}

	// Return the potential energy evaluated at position x
	double getPotential(double x) const {
		return potential(x);
	}

	// Return total energy
	double getEnergy(double x, double p) const {
		return kinetic(p) + potential(x);
	}
/*
	// Return the mass
	double getM() const {
		return kinetic.m;
	}

	// Return the restoring constant
	double getK() const {
		return potential.k;
	}
*/
	/* Setters */
	bool setM(double m) {
		bool status = false;
		if (m > 0) {
			kinetic = T(m);
			status = true;
		}
		return status;
		
	}
	bool setK(double k) {
		bool status = false;
		if (k > 0) {
			potential = V(k);
			status = true;
		}
		return status;
	}
private:
//	double m;	// Mass
//	double k;	// Spring constant

	// TODO These function definitions should eventually require
	// no input for the constructor. They should be able to access
	// the data of the external class directly.
	/* Function 1 - Kinetic energy part of hamiltonian */
	class T
	{
	public:
		T(double m) : m(m) {}

		double operator()(double p_0) {
			return std::pow(p_0, 2)/(2*m); 
		}
		friend class HarmonicOscillator;
	private:
		double m;
	};

	/* Function 2 - Potential energy part of hamiltonian */
	class V
	{
	public:
		V(double k) : k(k) {}

		double operator()(double x_0) {
			return k*pow(x_0, 2)/2;
		}
		friend class HarmonicOscillator;
	private:
		double k;
	};


	/* Functions variables */
	std::function<double(double)> kinetic;
	std::function<double(double)> potential;
};



int main(int argc, const char* argv[])
{
	processArgs(argc, argv);
	double h = std::atof(argv[1]);	// Set timestep to first program argument
	int N = std::atoi(argv[2]);	// Set number of iterations to second program argument

	HarmonicOscillator osc(1, 1);
	Integral integrate(FORWARD_EULER);

	double x_i = 1;
	double p_i = 0;

		/** Text to output **/
	int ttyfd = open("/dev/tty", O_RDWR);
	const char* msg = "Starting simulation...\n";
	write(ttyfd, msg, std::strlen(msg));
	Timer timer;
	timer.begin_timer();



	std::cout << N << std::endl;
	// Integrate
	for (int i = 0; i < N; i++) {
//		std::cout << i*h << " " << x_i << std::endl;				// Plot position vs time
//		std::cout << i*h << " " << osc.getEnergy(x_i, p_i) << std::endl;	// Plot energy vs time
		std::cout << p_i << " " << x_i << std::endl;				// Plot phase space
		std::cout << std::endl;
		
		x_i = integrate.flow( Derivative::evaluate(osc.getKinetic(), p_i, h), x_i, h );
		p_i = integrate.flow( -Derivative::evaluate(osc.getPotential(), x_i, h), p_i, h );

	}

		/** Text to output **/
	std::stringstream ss;
	ss << "Simulation complete. Total elapsed time: " << timer.end_timer()/1000000000.0 << " seconds.\n";
	std::string str = ss.str();
	msg = str.c_str();
	write(ttyfd, msg, std::strlen(msg));


	return 0;
}













/* Displays a help message to user and exits */
void helpMessage()
{
	std::cout << "Function testing.\n\
Usage:\n\
	./first timestep num_iterations\n\
	timestep	- the time (in seconds) for each iteration\n\
	num_iterations	- the total number of iterations" << std::endl << std::endl;
	exit(0);
}



/* Reports an error message and exits */
void error(std::string message)
{
	std::cout << "Error: " << message << std::endl;
	std::cout << "./first --help for usage." << std::endl;
	exit(1);
}



/* Ensures that the arguments given are valid
 * Program should take two arguments, the first of which
 * is an existing input file */
void processArgs(int argc, const char* argv[])
{
	std::string arg_1;

	// Check for correct number of arguments
	if (argc == 2) {
		arg_1 = argv[1];
		if (arg_1.compare("--help") == 0) {
			helpMessage();
		}
	}

	if (argc != 3) {
		error("Two arguments required.");
	}

	// TODO check that arguments are (double, int), both > 0
}





/*
class exponential
{
public:
	exponential(double A, double r) : A(A), r(r) {}

	double operator()(double t) {
		return A*std::exp(r*t);
	}

private:
	double r;	// Growth/decay rate
	double A;	// Starting value
};
*/


/*
class linear
{
public:
	linear(double a) : a(a) {}

	double operator()(double y_0) {
		return a*y_0;
	}
private:
	double a;
};

*/

