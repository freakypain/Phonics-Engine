#ifndef TIME_H
#define TIME_H

class Time
{
	private: // data members
		float mTime;		
		float mCurrentTime;
		float mDt;
		float mAccumulator;
		float mFps;		
		float mStartTime;
		int mFrames;


	public: // functons
		Time();
		~Time();		
		void update();
		float timer();
		unsigned int calcFps(int dt, int currentTime);
		float getTime();
		float getStep();
		unsigned int getFps();
};

#endif // TIME_H
