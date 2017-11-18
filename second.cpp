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

#include "Particle.h"
#include "Integral.h"
#include "Derivative.h"
#include "util.h"
#include "Particle.h"
#include "ParticleList.h"
#include "Simulate.h"

/* Function Prototypes */
void helpMessage();
void error(std::string message);
void processArgs(int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
	processArgs(argc, argv);
	double h = std::atof(argv[1]);	// Set timestep to first program argument
	int N = std::atoi(argv[2]);	// Set number of iterations to second program argument
	int numParticles = 1;

		/** Text to output **/
	int ttyfd = open("/dev/tty", O_RDWR);
	const char* msg = "Starting simulation...\n";
	write(ttyfd, msg, std::strlen(msg));
	Timer timer;
	timer.begin_timer();



	ParticleList list;
	for (int i = 0; i < numParticles; i++) {
		Particle* particle = new Particle(1.0, 1.0);
		list.add(particle);
	}

	Simulate::run(list, h, N);







		/** Text to output **/
	std::stringstream ss;
	ss << "Simulation complete. Total elapsed time: " << timer.end_timer()/1000000000.0 << " seconds.\n";
	std::string str = ss.str();
	msg = str.c_str();
	write(ttyfd, msg, std::strlen(msg));


	return 0;
}






/***********************************************
 *
 *		UTILITY FUNCTIONS
 *
 ***********************************************/

/* Displays a help message to user and exits */
void helpMessage()
{
	std::cout << "Function testing.\n\
Usage:\n\
	./secondtimestep num_iterations\n\
	timestep	- the time (in seconds) for each iteration\n\
	num_iterations	- the total number of iterations" << std::endl << std::endl;
	exit(0);
}



/* Reports an error message and exits */
void error(std::string message)
{
	std::cout << "Error: " << message << std::endl;
	std::cout << "./second --help for usage." << std::endl;
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




