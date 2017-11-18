/**
 *  Author: Conor Poland
 */

#ifndef PARTICLELIST_H
#define PARTICLELIST_H

#include <vector>
#include "Particle.h"

enum BindingPattern
{
	ALL,
	NN
};

class ParticleList
{
public:
	ParticleList() {}

	~ParticleList();

	void add(Particle* particle);

	void bind(BindingPattern pattern);

	int size() const;

	int length() const;

	void update();

	Particle* operator[](int index);
private:
	std::vector<Particle*> list;
};

#endif // PARTICLELIST_H
