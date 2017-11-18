/**
 *  Author: Conor Poland
 */

#include "ParticleList.h"


ParticleList::~ParticleList()
{
	for (int i = 0; i < list.size(); i++) {
		delete list[i];
	}
}

void ParticleList::add(Particle* particle)
{
	list.push_back(particle);
}

void ParticleList::bind(BindingPattern pattern)
{
	switch (pattern) {
	case ALL:
		for (int i = 0; i < list.size(); i++) {
			for (int j = 0; i < list.size(); j++) {
				if (i != j)
					list[i]->bind(list[j]);
					list[j]->bind(list[i]);
			}
		}
		break;
	case NN:
		break;
	}
}

int ParticleList::size() const
{
	return list.size();
}

int ParticleList::length() const
{
	return list.size();
}


void ParticleList::update()
{
	for (int i = 0; i < list.size(); i++) {
		list[i]->update();
	}
}

Particle* ParticleList::operator[](int index)
{
	return list[index];
}

