/**
 *  Author: Conor Poland
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cassert>
#include <functional>

#define G 0.03764

/** Functor class */
/*
template <class T>
class Functor
{
public:
	Functor() {}
	virtual double operator()(std::vector<double> p);
	virtual double operator()(std::vector<double> q, T* other);
};
*/

/** Kinetic energy class */
/*
template <class T>
class Kinetic : public Functor<T>
{
public:
	Kinetic(T* obj) : obj(obj) {}
	virtual double operator()(std::vector<double> p)
	{
		double sumOfSquares = 0;

		for (int i = 0; i < 3; i++)	// TODO 3 -> DIMENSION
			sumOfSquares += std::pow(p[i], 2);

		return sumOfSquares/(2.0*obj->getMass()); 
	}
private:
	T* obj;
};
*/

/** Potential energy class for gravitational potential */
/*
template <class T>
class Potential : public Functor<T>
{
public:
	Potential(T* obj) : obj(obj) {}
	virtual double operator()(std::vector<double> q, T* other)
	{
		double G = 1.0;
		double sumOfSquares = 0;
		double totalPotential = 0;

		for (int j = 0; j < 3; j++)	// Loop over the number of vector components
			sumOfSquares += std::pow( q[j] - other->getPosition(j), 2 );

		totalPotential -= G * obj->getMass() * other->getMass();
		totalPotential /= std::sqrt(sumOfSquares);

		return totalPotential;
	}
private:
	T* obj;
};
*/


/** Particle class */
class Particle
{
public:


	/** Functor class */
	class Functor
	{
	public:
		Functor() {}
		virtual double operator()(std::vector<double> p) = 0;
		virtual double operator()(std::vector<double> q, Particle* other) = 0;
	};

	/** Kinetic energy class */
	class Kinetic : public Functor
	{
	public:
		Kinetic(Particle* obj) : obj(obj) {}
		virtual double operator()(std::vector<double> q, Particle* other) { return -1.0; }
		virtual double operator()(std::vector<double> p)
		{
			double sumOfSquares = 0;

			for (int i = 0; i < 3; i++)	// TODO 3 -> DIMENSION
				sumOfSquares += std::pow(p[i], 2);

			return sumOfSquares/(2.0*obj->getMass()); 
		}
	private:
		Particle* obj;
	};


	/** Potential energy class for gravitational potential */
	class Potential : public Functor
	{
	public:
		Potential(Particle* obj) : obj(obj) {}
		virtual double operator()(std::vector<double> p) { return -1.0; }
		virtual double operator()(std::vector<double> q, Particle* other)
		{
			double epsilon = 0.0005;	// Softening term
			double sumOfSquares = 0;
			double totalPotential = 0;

			for (int k = 0; k < 3; ++k) {	// Loop over the number of vector components
				sumOfSquares += std::pow( q[k] - other->getPosition(k), 2 );
			}

			totalPotential -= G * obj->getMass() * other->getMass();
			totalPotential /= ( std::sqrt(sumOfSquares) + epsilon );

			return totalPotential;
		}
	private:
		Particle* obj;
	};




	Particle(double m, std::vector<double> q_init, std::vector<double> p_init)
	: m(m), temp_m(m),
	  q(),  temp_q(),
	  p(),  temp_p()
	{
		for (int k = 0; k < q_init.size(); ++k) {
			q.push_back(q_init[k]);
			temp_q.push_back(q[k]);
		}

		for (int k = 0; k < p_init.size(); ++k) {
			p.push_back(p_init[k]);
			temp_p.push_back(p[k]);
		}

		kinetic = Kinetic(this);
		potential = Potential(this);
	}


	/** Getters */
	double getMass() const;

	double getPosition(int i) const;
	double getMomentum(int i) const;

	std::vector<double> getPosition() const;
	std::vector<double> getMomentum() const;
	std::vector<double> getTempPosition() const;
	std::vector<double> getTempMomentum() const;

	/*
	double getKinetic(std::vector<double>);
	double getPotential(std::vector<double>, Particle*);
	std::function<double(std::vector<double>)> getKinetic();
	std::function<double(std::vector<double>, Particle*)> getPotential();
	*/

	double getKinetic(std::vector<double> p)
	{
		return kinetic(p);
	}
	double getPotential(std::vector<double> q, Particle* other)
	{
		return potential(q, other); 
	}

	std::function<double(std::vector<double>)> getKinetic()
	{
		return kinetic;
	}
	std::function<double(std::vector<double>, Particle*)> getPotential()
	{
		return potential;
	}


	/** Setters */
	void setMass(double m);

	void setPosition(int i, double val);
	void setMomentum(int i, double val);

	void setPosition(std::vector<double> vals);
	void setMomentum(std::vector<double> vals);

	/** Update the data from temporary storage */
	void update();

	/** Print the particle data */
        friend std::ostream& operator<<(std::ostream& os, const Particle& particle);
private:
	// Data
	double m;
	std::vector<double> q;
	std::vector<double> p;

	// Temporary data
	double temp_m;
	std::vector<double> temp_q;
	std::vector<double> temp_p;

	// Energy functions
	std::function<double(std::vector<double>)> kinetic;
	std::function<double(std::vector<double>, Particle*)> potential;
};

#endif // PARTICLE_H



