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

	AllocConsole();
	AttachConsole( GetCurrentProcessId() );
	FILE* fOut;
	freopen_s(&fOut, "conout$", "w", stdin);
	fclose(fOut);

	//HANDLE consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );


	/*
	DWORD cCharsWritten;
	char* str = TEXT("enter game command");
	WriteConsole(consoleHandle, str, strlen(str), &cCharsWritten, NULL);
	char* command = malloc(100);
	int charsRead = 0;
	ReadConsole(consoleHandle, command, 100, &cCharsRead, NULL);*/
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


