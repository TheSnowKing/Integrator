/**
 *  Author: Conor Poland
 */

#include "ParticleList.h"
/** Destructor */
ParticleList::~ParticleList()
{
	for (int i = 0; i < list.size(); i++)
		delete list[i];
}

/**
 * Add - adds a new particle to the list
 *
 * @param particle The particle to enter into the list
 */
void ParticleList::add(Particle* particle)
{
	list.push_back(particle);
}


/**
 * Size - return the number of entries in the list
 *
 * @return The size of the list
 */
int ParticleList::size() const
{
	return list.size();
}


/**
 * Length - return the number of entries in the list
 *
 * @return The size of the list
 */
int ParticleList::length() const
{
	return list.size();
}


/** Update - update all particles in the list */
void ParticleList::update()
{
	for (int i = 0; i < list.size(); i++) {
		list[i]->update();
	}
}


/**
 * [] - access an entry in the list
 *
 * @param index The index in the list to access
 * @return A pointer to the particle at the given index
 */
Particle* ParticleList::operator[](int index)
{
	return list[index];
}
