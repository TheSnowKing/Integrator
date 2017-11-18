/**
 *  Author: Conor Poland
 */

#include "Simulate.h"

void Simulate::run(ParticleList& list, double h, int N)
{
	std::vector<double> gradT;	// Gradient of kinetic energy
	std::vector<double> gradV;	// Gradient of potential energy
	Integral integrate(FORWARD_EULER);

	std::cout << N << std::endl;
	for (int i = 0; i < N; i++) {		// Loop over timesteps
		for (int j = 0; j < list.size(); j++) {		// Loop over number of particles
	//		std::cout << i*h << " " << list[j]->getPosition(0) << std::endl;	// Plot position vs time
	//		std::cout << i*h << " " << osc.getEnergy(x_i, p_i) << std::endl;	// Plot energy vs time
			std::cout << list[j]->getPosition(0) << " " << list[j]->getMomentum(0) << std::endl;				// Plot phase space
			std::cout << std::endl;


			std::vector<double> x_;	// Vector for position at the next time step
			std::vector<double> p_; // Vector for momentum at the next time step

			/*
			 *	FIRST METHOD - Strang Splitting
			 */
			// Obtain the gradient of the potential
			gradV = Derivative::evaluate(list[j]->getPotential(), list[j]->getPosition(), h);
			for (int i = 0; i < gradV.size(); i++)
				gradV[i] = -gradV[i];

			// Update momentum by integrating potential energy
			p_ = integrate.flow(gradV, list[j]->getMomentum(), h/2);
			list[j]->setMomentum(p_);

			// Obtain gradient of kinetic energy
			gradT = Derivative::evaluate(list[j]->getKinetic(), list[j]->getTempMomentum(), h);

			// Update position by integrating kinetic energy
			x_ = integrate.flow(gradT, list[j]->getPosition(), h);
			list[j]->setPosition(x_);

			// Obtain the gradient of the potential
			gradV = Derivative::evaluate(list[j]->getPotential(), list[j]->getPosition(), h);
			for (int i = 0; i < gradV.size(); i++)
				gradV[i] = -gradV[i];

			// Update momentum by integrating potential energy
			p_ = integrate.flow(gradV, list[j]->getMomentum(), h/2);
			list[j]->setMomentum(p_);


/*
			// Obtain derivatives
			gradT = Derivative::evaluate(list[j]->getKinetic(), list[j]->getMomentum(), h);
			gradV = Derivative::evaluate(list[j]->getPotential(), list[j]->getPosition(), h);
			for (int i = 0; i < gradV.size(); i++)
				gradV[i] = -gradV[i];


			// Update momentum by integrating potential energy
			p_ = integrate.flow(gradV, list[j]->getMomentum(), h/2);
			list[j]->setMomentum(p_);

			// Update position by integrating kinetic energy
			x_ = integrate.flow(gradT, list[j]->getPosition(), h);
			list[j]->setPosition(x_);

			// Update momentum by integrating potential energy
			p_ = integrate.flow(gradV, list[j]->getMomentum(), h/2);
			list[j]->setMomentum(p_);
*/




			/*
			 *	SECOND METHOD - Euler-A
			 */

			// Obtain gradient of kinetic energy
			gradT = Derivative::evaluate(list[j]->getKinetic(), list[j]->getMomentum(), h);

			// Update position by integrating kinetic energy
			x_ = integrate.flow(gradT, list[j]->getPosition(), h);
			list[j]->setPosition(x_);

			// Obtain gradient of potential energy using newly calculated positions in temporary buffer
			gradV = Derivative::evaluate(list[j]->getPotential(), list[j]->getTempPosition(), h);
			for (int i = 0; i < gradV.size(); i++)
				gradV[i] = -gradV[i];

			// Update momentum by integrating potential energy
			p_ = integrate.flow(gradV, list[j]->getMomentum(), h);
			list[j]->setMomentum(p_);
		}

		list.update();	// Update the particle list with calculated values for the timestep
	}
}

