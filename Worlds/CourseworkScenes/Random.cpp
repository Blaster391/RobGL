#include "Random.h"

#include <random>

Random::Random()
{
}


Random::~Random()
{
}

float Random::random()
{
	return (float)rand()/RAND_MAX;
}
