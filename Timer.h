#ifndef TIMER_H
#define TIMER_H

#include<windows.h>

namespace Engine
{
	class Timer
	{
	public:
		Timer();
		void calculateDeltaTime(void);
		void calculateTotalTime(void);
		void calculateFrameRate(void);
		float deltaTime(void);
		float totalTime(void);
		int frameRate(void);

	private:
		int frameCount,fps;
		float dt_time, tt_time, sec_perCnts;
		_int64 cntsPrev;
	};//End of Class
}; //End of namespace

#endif 