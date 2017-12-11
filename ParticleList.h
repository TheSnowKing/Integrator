/**
 *  @author Conor Poland
 */

#ifndef PARTICLELIST_H
#define PARTICLELIST_H

#include <vector>
#include "Particle.h"

class ParticleList
{
public:
	/* Constructor */
	ParticleList() {}


	/* Destructor */
	~ParticleList();


	/**
	 * Add - adds a new particle to the list
	 *
	 * @param particle The particle to enter into the list
	 */
	void add(Particle* particle);


	/**
	 * Size - return the number of entries in the list
	 *
	 * @return The size of the list
	 */
	int size() const;


	/**
	 * Length - return the number of entries in the list
	 *
	 * @return The size of the list
	 */
	int length() const;


	/** Update - update all particles in the list */
	void update();


	/**
	 * [] - access an entry in the list
	 *
	 * @param index The index in the list to access
	 * @return A pointer to the particle at the given index
	 */
	Particle* operator[](int index);
private:
	std::vector<Particle*> list;	// The particle list
};

#endif // PARTICLELIST_H
