#include"Engine.h"
#ifndef MATHF_H
#define MATHF_H

namespace Engine
{
	class Mathf
	{
	public:
		void SeedRand(UINT value);
		//Minimum Inclusive , Maximum Inclusive
		int Random(int min, int max);
	private:
		UINT seed;
	};
};

#endif // !1

