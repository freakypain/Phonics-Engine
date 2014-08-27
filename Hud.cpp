#include <cassert>

//#include "FPS.hpp"
#include "RenderPoint.hpp"
#include "Hud.hpp"


// TODO Fixing hud display

Hud::Hud( RenderPoint* renderer ) // : window( aWindow )
{
	assert( renderer != 0 );
}

Hud::~Hud()
{
	//dtor
}


void Hud::draw()
{
	//glDisable( GL_CULL_FACE ); // needed for text, dont know why

	// Draw it
	//assert ( window != NULL );
	//window->pushGLStates();
	//window->popGLStates();
}
