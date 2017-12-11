/**
 *  Author: Conor Poland
 */

#ifndef SIMULATE_H
#define SIMULATE_H

#include <vector>
#include <cmath>
#include "Integral.h"
#include "Derivative.h"
#include "Particle.h"
#include "ParticleList.h"

class Simulate
{
public:
	static void run(ParticleList& list, double h, int N, int mode);
};
#endif // SIMULATE_H
