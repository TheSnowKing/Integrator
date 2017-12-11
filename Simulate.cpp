/**
 *  Author: Conor Poland
 */

#include "Simulate.h"

#define G 0.03764

void Simulate::run(ParticleList& list, double h, int N, int mode)
{
	std::cout << N << std::endl;

	// Variables
	Integral integrate(FORWARD_EULER);
	std::vector<double> x_;	// Vector for position at the next time step
	std::vector<double> p_; // Vector for momentum at the next time step
	int M = list.size();	// Number of particles

	double prevPotential = 0;
	for (int i = 0; i < M-1; i++) {
		for (int j = i; j < M; j++) {
			prevPotential += list[i]->getPotential(list[i]->getPosition(), list[j]);
		}
	}
	double initPotential = prevPotential;

	for (int n = 0; n < N; ++n) {	// Loop over timesteps


		// Output data for current timestep
		switch (mode) {
		case 0:

			// ****************************************************************
			//                       PLOT - position data
			// ****************************************************************

			for (int i = 0; i < M; ++i) {
				std::cout << list[i]->getPosition(0) << " " << list[i]->getPosition(1) << " " << list[i]->getPosition(2) <<std::endl;
			}
			std::cout << std::endl;
			break;

		case 1:


			// ****************************************************************
			//                       PLOT - energy data
			// ****************************************************************

			double kinetic = 0;
			for (int i = 0; i < M; i++) {
				kinetic += list[i]->getKinetic(list[i]->getMomentum());
			}

			double potential = 0;
			for (int i = 0; i < M-1; i++) {
				for (int j = i; j < M; j++) {
					potential += list[i]->getPotential(list[i]->getPosition(), list[j]);
				}
			}

			potential -= initPotential;
			double energy = kinetic + potential;
			std::cout << n*h << " " << potential << " " << kinetic << " " << energy << std::endl;

			break;
		}

	

		// ****************************************************************
		//                     Calculate next timestep 
		// ****************************************************************

		for (int i = 0; i < M; i++) {	// Loop over all particles
			std::vector<double> gradT(3, 0);	// Gradient of kinetic energy
			std::vector<double> gradV(3, 0);	// Gradient of potential energy






			//
			// STEP 1 - Apply flow map using potential energy
			//


			// Obtain the gradient of the potential by summing over constributions from all other particles
/*			TODO Using derivatives
			for (int j = 0; j < M; ++j) {	// Loop over all particles j != i
				if (j != i) {

					std::vector<double> gradV_j = Derivative::evaluate(list[i]->getPotential(), list[j], list[i]->getPosition(), h);
					for (int k = 0; k < 3; ++k)
						gradV[k] = -gradV_j[k];
				}
			}
*/
			for (int j = 0; j < M; j++) {	// Loop over all particles j != i
				if (j != i) {
					std::vector<double> pos_i = list[i]->getPosition(); // position for particle i
					std::vector<double> pos_j = list[j]->getPosition(); // position for particle j

					double m_i = list[i]->getMass();
					double m_j = list[j]->getMass();

					double dx = pos_i[0] - pos_j[0];
					double dy = pos_i[1] - pos_j[1];
					double dz = pos_i[2] - pos_j[2];

					double r = std::sqrt( dx*dx + dy*dy + dz*dz );
					double r3 = r*r*r;

					dx = dx/r3;
					dy = dy/r3;
					dz = dz/r3;

					gradV[0] += -G*m_i*m_j*dx;
					gradV[1] += -G*m_i*m_j*dy;
					gradV[2] += -G*m_i*m_j*dz;
				}
			}

			// Integrate the flow with the potential energy to calculate the momentum
			p_ = integrate.flow(gradV, list[i]->getMomentum(), h/2);
			list[i]->setMomentum(p_);




			
			//
			// STEP 2 - Apply flow map using kinetic energy
			//

			// Obtain gradient of kinetic energy using the newly calculated momenta
//			gradT = Derivative::evaluate(list[i]->getKinetic(), list[i]->getTempMomentum(), h);
			
			gradT[0] = list[i]->getTempMomentum()[0]/list[i]->getMass();
			gradT[1] = list[i]->getTempMomentum()[1]/list[i]->getMass();
			gradT[2] = list[i]->getTempMomentum()[2]/list[i]->getMass();

			// Integrate the flow with the kinetic energy to calculate the position
			x_ = integrate.flow(gradT, list[i]->getPosition(), h);
			list[i]->setPosition(x_);





			//
			// STEP 3 - Apply flow map using potential energy
			//

			// Obtain the gradient of the potential by summing over constributions from all other particles
/*			TODO Using derivatives
			for (int j = 0; j < M; ++j) {	// Loop over all particles j != i
				if (j != i) {
					std::vector<double> gradV_j = Derivative::evaluate(list[i]->getPotential(), list[j], list[i]->getTempPosition(), h);

					for (int k = 0; k < 3; ++k)
						gradV[k] = -gradV_j[k];
				}
			}
*/
			for (int j = 0; j < M; ++j) {	// Loop over all particles j != i
				if (j != i) {
					std::vector<double> pos_i = list[i]->getTempPosition(); // position for particle i
					std::vector<double> pos_j = list[j]->getTempPosition(); // position for particle j

					double m_i = list[i]->getMass();
					double m_j = list[j]->getMass();

					double dx = pos_i[0] - pos_j[0];
					double dy = pos_i[1] - pos_j[1];
					double dz = pos_i[2] - pos_j[2];

					double r = std::sqrt( dx*dx + dy*dy + dz*dz );
					double r3 = r*r*r;

					dx = dx/r3;
					dy = dy/r3;
					dz = dz/r3;

					gradV[0] += -G*m_i*m_j*dx;
					gradV[1] += -G*m_i*m_j*dy;
					gradV[2] += -G*m_i*m_j*dz;
				}
			}

			// Integrate the flow with the potential energy to calculate the momentum
			p_ = integrate.flow(gradV, list[i]->getMomentum(), h/2);
			list[i]->setMomentum(p_);

		}
		list.update();	// Update the particle list with calculated values for the timestep
	}
}

/*
void Simulate::run(ParticleList& list, double h, int N)
{
	std::vector<double> gradT;	// Gradient of kinetic energy
	std::vector<double> gradV;	// Gradient of potential energy
	Integral integrate(FORWARD_EULER);

	std::cout << N << std::endl;
	for (int i = 0; i < N; i++) {		// Loop over timesteps
		for (int j = 0; j < list.size(); j++) {		// Loop over number of particles
	//		std::cout << i*h << " " << list[j]->getPosition(0) << std::endl;	// Plot position vs time
	//		std::cout << i*h << " " << osc.getEnergy(x_i, p_i) << std::endl;	// Plot energy vs time TODO UPDATE
			std::cout << list[j]->getPosition(0) << " " << list[j]->getMomentum(0) << std::endl;	// Plot phase space
			std::cout << std::endl;


			std::vector<double> x_;	// Vector for position at the next time step
			std::vector<double> p_; // Vector for momentum at the next time step

			//
			//	FIRST METHOD - Strang Splitting
			//
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



			//
			//	SECOND METHOD - Euler-A
			//

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
*/
