#include <iostream>
#include "Engine.hpp"

int main()
{
    std::cout << "Starting Engine" << std::endl;

    Engine * engine = new Engine();
		engine->build();
		engine->run();
		engine->stop();
	delete engine;
    return 0;
}



