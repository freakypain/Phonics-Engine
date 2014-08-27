#ifndef TIME_H
#define TIME_H

class Time
{
	private: // data members
		//static sf::Clock clock;
		//static float currentTime;
		//static float deltaTime;
		static double deltatime;

	private: // disable creation of time object
		//Time(){}

	public: // functons
		Time();
		static void update();
		static float now();
		static float step();

};

#endif // TIME_H
