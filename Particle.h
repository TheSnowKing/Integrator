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

/** Functor class
 */
class Functor
{
public:
	Functor() {}
	virtual double operator()(std::vector<double> param) = 0; 
};



/** Kinetic class
 */
template <class T>
class Kinetic : public Functor
{
public:
	Kinetic(T* obj) : obj(obj) {}
	virtual double operator()(std::vector<double> p)
	{
		double sumOfSquares = 0;

		for (int i = 0; i < p.size(); i++) {
			sumOfSquares += std::pow(p[i], 2);
		}

		return sumOfSquares/(2.0*obj->getMass()); 

	}
private:
	T* obj;
};



/** Potential class
 */
template <class T>
class Potential : public Functor
{
public:
	Potential(T* obj) : obj(obj) {}
	virtual double operator()(std::vector<double> x)
	{
		double sumOfSquares = 0;


		for (int i = 0; i < x.size(); i++) {
			sumOfSquares += std::pow(x[i], 2);
		}

		return obj->getK()*sumOfSquares/2.0;
	}
private:
	T* obj;
};



/** Particle class
 */
class Particle
{
public:
	Particle(double m = 1, double k = 1);

	/* Getters */
	double getMass() const;
	double getK() const;
	double getPosition(int i) const;
	double getMomentum(int i) const;
	std::vector<double> getPosition() const;
	std::vector<double> getMomentum() const;
	std::vector<double> getTempPosition() const;
	std::vector<double> getTempMomentum() const;


	/* Setters */
	void setMass(double m);
	void setPosition(int i, double val);
	void setMomentum(int i, double val);

	void setPosition(std::vector<double> vals);
	void setMomentum(std::vector<double> vals);

	/* Bind this particle to other */
	bool bind(Particle* other);

	/* Update the data from temporary storage */
	void update();
	double getKinetic(std::vector<double> p);
	double getPotential(std::vector<double> x);
	std::function<double(std::vector<double>)> getKinetic();
	std::function<double(std::vector<double>)> getPotential();
/*
	double getEnergy() {

	}
*/

        friend std::ostream& operator<<(std::ostream& os, const Particle& particle);
private:
	// Data
	double m;
	double k;
	std::vector<double> q;
	std::vector<double> p;

	// Temporary data
	double temp_m;
	double temp_k;
	std::vector<double> temp_q;
	std::vector<double> temp_p;

	// Binding vector
	std::vector<Particle*> bindings;

	// Energy functions
	std::function<double(std::vector<double>)> kinetic;
	std::function<double(std::vector<double>)> potential;
};

#endif // PARTICLE_H



