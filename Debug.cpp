#include "Debug.hpp"

#include <iostream>
#include <Windows.h>

#include <cstdlib>


Debug::Debug()
{	
	setConsole(); // Temp debug console visible
}

Debug::~Debug()
{

}

// Log Messages
struct logMessage{
	static logMessage& print()
	{
		static logMessage printMessage;
		return printMessage;
	}

	template< class T >
	logMessage &operator<<(T output)
	{
		std::cout << output;
		return *this;
	}

private:
	logMessage() {};
};



// Set console visible
void Debug::setConsole( )
{
	mShowConsole = true;

	FILE *conin, *conout;
	AllocConsole();
	AttachConsole( GetCurrentProcessId() );
	freopen_s(&conin, "conin$", "r", stdin);
	freopen_s(&conout, "conout$", "w", stdout);
	freopen_s(&conout, "conout$", "w", stderr);
}

void Debug::hideConsole()
{
	mShowConsole = false;
}

bool Debug::getConsole()
{
	return mShowConsole;
}

void Debug::showConsole()
{

}


