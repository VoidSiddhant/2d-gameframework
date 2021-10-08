#include "Mathf.h"

namespace Engine
{
	void Mathf::SeedRand(UINT value)
	{
		seed = value;
		srand(seed);
	}
	int Mathf::Random(int min, int max)
	{
		return rand() % max + min;
	}
};