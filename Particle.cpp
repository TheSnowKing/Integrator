/**
 *  Author: Conor Poland
 */

#include "Particle.h"


/** Constructor */
/*
Particle::Particle(double m, double k)
: m(m), temp_m(m),
  k(k), temp_k(k),
  q(3, 1), p(3, 2),		// TODO change 3 -> DIMENSION
  temp_q(3, 0), temp_p(3, 0),
  bindings()
{
	q[0] = 1;
	q[1] = 0;
	q[2] = 0;

	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	kinetic = Kinetic<Particle>(this);
	potential = Potential<Particle>(this);
}
*/


/**
 * ----------------------------------------------------------------
 *                            GETTERS
 * ---------------------------------------------------------------- 
 */
double Particle::getMass() const
{
	return m;
}

double Particle::getPosition(int i) const
{
	return q[i];
}
double Particle::getMomentum(int i) const
{
	return p[i];
}

std::vector<double> Particle::getPosition() const
{
	return q;
}
std::vector<double> Particle::getMomentum() const
{
	return p;
}

std::vector<double> Particle::getTempPosition() const
{
	return temp_q;
}
std::vector<double> Particle::getTempMomentum() const
{
	return temp_p;
}

/* TODO Either figure out how to link these with templating, or remove
double Particle::getKinetic(std::vector<double> p)
{
	return kinetic(p);
}
double Particle::getPotential(std::vector<double> q, Particle* other)
{
	return potential(q, other); 
}

std::function<double(std::vector<double>)> Particle::getKinetic()
{
	return kinetic;
}
std::function<double(std::vector<double>, Particle*)> Particle::getPotential()
{
	return potential;
}
*/

/**
 * ----------------------------------------------------------------
 *                            SETTERS
 * ---------------------------------------------------------------- 
 */
void Particle::setMass(double m)
{
	this->temp_m = m;
}

void Particle::setPosition(int i, double val)
{
	assert((i >= 0) && (i < 3));
	temp_q[i] = val;
}
void Particle::setMomentum(int i, double val)
{
	assert((i >= 0) && (i < 3));
	temp_p[i] = val;
}

void Particle::setPosition(std::vector<double> vals)
{
	int size = vals.size();
	assert((size > 0) && size <= 3);
	assert(size == q.size());

	for (int i = 0; i < size; i++)
		temp_q[i] = vals[i];
}
void Particle::setMomentum(std::vector<double> vals)
{
	int size = vals.size();
	assert((size > 0) && size <= 3);
	assert(size == p.size());

	for (int i = 0; i < size; i++)
		temp_p[i] = vals[i];
}



/**
 * ----------------------------------------------------------------
 *                        MEMBER FUNCTIONS
 * ---------------------------------------------------------------- 
 */


/** Update the data from temporary storage */
void Particle::update()
{
	m = temp_m;
	for (int i = 0; i < 3; i++) {
		q[i] = temp_q[i];
		p[i] = temp_p[i];
	}
}

std::ostream& operator<<(std::ostream& os, const Particle& particle)
{
	os << "temp Position: [" << particle.temp_q[0] << ", " << particle.temp_q[1] << ", " << particle.temp_q[2] << "]\n";
	os << "temp Momentum: [" << particle.temp_p[0] << ", " << particle.temp_p[1] << ", " << particle.temp_p[2] << "]\n";

	os << "Mass: " << particle.m << "\n";
	os << "Position: [" << particle.q[0] << ", " << particle.q[1] << ", " << particle.q[2] << "]\n";
	os << "Momentum: [" << particle.p[0] << ", " << particle.p[1] << ", " << particle.p[2] << "]\n";
	return os;
}

