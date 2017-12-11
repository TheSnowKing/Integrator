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
#include <ctime>

#include "Particle.h"
#include "util.h"
#include "Simulate.h"


#define G 0.03764
#define pi 3.1415926525

/* Function Prototypes */
void helpMessage();
void error(std::string message);
void processArgs(int argc, const char* argv[]);

/** Return value between low and high (inclusive) */
double getRand(double low, double high)
{
//	return (std::rand() % (int)(high - low + 1)) + low;
	double flt = (double)rand() / RAND_MAX;
	return low + flt*(high - low);
}


int main(int argc, const char* argv[])
{
	std::srand(std::time(0));

	processArgs(argc, argv);

	double h = std::atof(argv[1]);	// Set timestep to first program argument
	int N = std::atoi(argv[2]);	// Set number of iterations to second program argument

	
	int mode = 0;
	if (argc == 4) {
		mode = std::atoi(argv[3]);	// Output mode, 0 - data, 1 - energy
	}

	int numParticles = 100;

		/** Text to output **/
	int ttyfd = open("/dev/tty", O_RDWR);
	const char* msg = "Starting simulation...\n";
	write(ttyfd, msg, std::strlen(msg));
	Timer timer;
	timer.begin_timer();


	ParticleList list;
//	list.add(new Particle(10047.926, {0.0024, 0.00318, -0.00008}, {1047.926*0.000129, 1047.926*0.002, 0}));
	list.add(new Particle(1000, {0, 0, 0}, {0, 0, 0}));
	

	for (int i = 0; i < numParticles; i++) {
		double m = getRand(0.0001,0.0005);

		double R = getRand(2,6);
		double theta = getRand(0, 2*pi);

		double r_x = R*cos(theta);
		double r_y = R*sin(theta);
		double r_z = getRand(-0.1,0.1);

		if (r_x > 0)
			r_x += 1;
		else
			r_x -= 1;

		if (r_y > 0)
			r_y += 1;
		else
			r_y -= 1;

		std::vector<double> centerPos = list[0]->getPosition();

		double dx = r_x - centerPos[0] + 0.001;
		double dy = r_y - centerPos[1] + 0.001;
		double dz = r_z - centerPos[2] + 0.001;

		double r = std::sqrt( dx*dx + dy*dy + dz*dz );

		dx = dx/r;
		dy = dy/r;
		dz = dz/r;
		
		double p = m*std::sqrt( G*list[0]->getMass()/(2*r) );

		double p_x = p*dy;
		double p_y = -p*dx;
		double p_z = p*dz;

		std::vector<double> position = { r_x, r_y, r_z };
		std::vector<double> momentum = { p_x, p_y, p_z };

		list.add(new Particle(m, position, momentum));
	}


	Simulate::run(list, h, N, mode);







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

	if ((argc != 3) && (argc != 4)) {
		error("Two arguments required.");
	}

	// TODO check that arguments are (double, int), both > 0
}




