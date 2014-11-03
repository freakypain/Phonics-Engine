#include "Time.hpp"

#include <Windows.h>
#include <ctime>
#include <iostream>

/** Time()
* Initialize Time
*/
Time::Time() : mTime(0.0f), mCurrentTime(0.0f), mDt(0.1f), mAccumulator(0.0f), 
				mFps(0.0f), mFrames(0), mStartTime(0.0f)
{

}

/** Time()
* Deconstruct Time
*/
Time::~Time() 
{ 

}

/** timer()
* Set Windows.h timer
*/
float Time::timer()
{
	static __int64 start = 0;
	static __int64 frequency = 0;

	if (start == 0)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		return 0.0f;
	}

	__int64 counter = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter);
	return (float)((counter - start) / double(frequency));
}

/** update()
* Update time step & time
*/
void Time::update()
{
	const float newTime = Time::timer();
	float deltaTime = newTime - mCurrentTime;
	mCurrentTime = newTime;

	if (deltaTime > 0.25f)
			deltaTime = 0.25f;

	mAccumulator += deltaTime;

	while ( mAccumulator >= mDt )
	{
		mAccumulator -= mDt;
		mTime += mDt;
	}

	// Set Fps
	mFps = calcFps(deltaTime, mCurrentTime);
}

/** getTime()
* Current Timer
* @return float currentTime
*/
float Time::getTime()
{
	return mCurrentTime;
}

/** getStep()
* Current Time Step
* @return float current time step
*/
float Time::getStep()
{
	return mTime;
}

/** getFps()
* Frames Per Second (60)
* @return float current Frames Per Second
*/
unsigned int Time::getFps()
{
	return mFps;
}

/** calcFps()
* Calculate Frames Per Second
*/
unsigned int Time::calcFps(int dt, int currentTime)
{
	unsigned int fps = mFps;
	++mFrames;
	
	if (currentTime - mStartTime >= 1.0f)
	{
		fps = mFrames;
		mFrames = 0;
		mStartTime = currentTime;
	}

	return fps;
}