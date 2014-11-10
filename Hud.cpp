// Includes
#include "RenderPoint.hpp"
#include "Hud.hpp"

// External
#include <gl\GL.h>


// TODO Fixing hud display
Hud::Hud( )
{
	set2D();
}

Hud::~Hud()
{
	//dtor
}

void Hud::set2D()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Get Window Height & Width
//	RECT rect;
//	int windowWidth = rect.right - rect.left;
//	int windowHeight = rect.bottom - rect.top;

//	glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.375, 0.375, 0.0);

	glDisable(GL_DEPTH_TEST);
}

void Hud::draw()
{

	//glDisable( GL_CULL_FACE ); // needed for text, dont know why

	// Draw it
	//assert ( window != NULL );
	//window->pushGLStates();
	//window->popGLStates();
}
