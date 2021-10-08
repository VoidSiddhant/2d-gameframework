
#include"Timer.h"

namespace Engine
{
	Timer::Timer()
	{
		_int64 cnts_perSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&cnts_perSec);
		sec_perCnts = 1.0f / cnts_perSec;
		QueryPerformanceCounter((LARGE_INTEGER*)&cntsPrev);
		fps = 0;
		tt_time = 0.0f;
		dt_time = 0.0f;
		frameCount = 0;
	}

	void Timer::calculateDeltaTime()
	{
		_int64 cntsCurr;
		QueryPerformanceCounter((LARGE_INTEGER*)&cntsCurr);
		dt_time = (cntsCurr - cntsPrev) * sec_perCnts;
		cntsPrev = cntsCurr;

	}

	void Timer::calculateTotalTime()
	{
		tt_time += dt_time;
	}

	void Timer::calculateFrameRate()
	{
		frameCount++;
		static float timeElapsed = 0.0f;
		timeElapsed += dt_time;
		if (timeElapsed >= 1.0f)
		{
			fps = frameCount / timeElapsed;
			timeElapsed = 0.0f;
			frameCount = 0;
		}
	}

	float Timer::deltaTime()
	{
		return dt_time;
	}

	float Timer::totalTime()
	{
		return tt_time;
	}

	int Timer::frameRate()
	{
		return fps;
	}
}; //End Namespace