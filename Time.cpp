#include "Time.hpp"

#include <ctime>
#include <iostream>

//sf::Clock Time::clock;
//float Time::currentTime = 0.0f;
//float Time::deltaTime = 0.0f;

// TODO Fix time 


Time::Time()
{
	//clock_t begin = clock();
}

void Time::update()
{
	
	//float newTime = clock.getElapsedTime().asSeconds();
	//deltaTime = newTime - currentTime;
	//currentTime = newTime;
}

float Time::now()
{
	//return currentTime;
	return 1.0f; // Temp returning value value
}

float Time::step()
{
	//return deltaTime;
	return 1.0f; // Temp returning value value
}
