#ifndef DEBUG_H
#define DEBUG_H


class Debug{	

	public:
		Debug();
		~Debug();
		void setConsole();
		void hideConsole();
		bool getConsole();

		void showConsole();
		
	private:
		void writeLog();
		void createLog();
		void clearLog();

		bool mShowConsole;


};

#endif

