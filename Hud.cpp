#include <cassert>
#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include "FPS.hpp"
#include "Hud.hpp"



Hud::Hud( sf::RenderWindow * aWindow ) : window( aWindow )
{
	assert ( window != NULL );
}

Hud::~Hud()
{
	//dtor
}


void Hud::draw()
{
	glDisable( GL_CULL_FACE ); // needed for text, dont know why

	// Draw it
	assert ( window != NULL );
	window->pushGLStates();
	window->popGLStates();
}
