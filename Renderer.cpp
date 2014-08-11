// Internal
#include "Renderer.hpp"
#include "ShaderProgram.hpp"
#include "GameObject.hpp"
#include "Texture.hpp"
#include "Time.hpp"

// External
#include <gl\GL.h>
#include <cassert>


Renderer::Renderer( RenderPoint* renderPoint ) :  program( NULL )
{
	mRenderPoint = renderPoint;
}

Renderer::~Renderer()
{
	delete program;
}

void Renderer::setShader( ShaderProgram * aProgram )
{
	program = aProgram;
	program->use(); // this is the default program
	findLocations(); // find where to put the uniforms to
}

void Renderer::setProjection( glm::mat4 aProjection )
{
	projection = aProjection; // cache P matrix
}

void Renderer::setView( glm::mat4 aView )
{
	view = aView; // cache V matrix
}

void Renderer::setModel( glm::mat4 aModel )
{
	model = aModel; // cache M matrix
}

void Renderer::setLight( glm::vec3 aLight )
{
	light = aLight; // cache light prosition for positional light
}

void Renderer::setTexture0( Texture * aTex ) // for single texture at a time, otherwise use activeTexture
{
	tex0 = aTex->getId();
}


void Renderer::setTime( float aTime )
{
	time = aTime; // set time for use in vs and fs
}

ShaderProgram * Renderer::getShaderProgram()
{
    return program;
}

bool Renderer::draw()
{
	// Render horizontal lines
	for (int u = nextLine; i < mRenderPoint->getHeight(); y++)
	{
		// Start interpolating from left side of view plane
		mCurrentX = mViewPlaneX1;

	}

}


/*
void Renderer::draw( GameObject * aWorld )
{
   // std::cout << program->getProgramID() << " ";
	program->use(); // make sure default shader program is used

	glEnable( GL_DEPTH_TEST );

	//glEnable( GL_CULL_FACE ); // defaul GL_BACK

	glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear screen 0
	time = Time::now(); // provide the shader with time float in seconds, for later use !
	aWorld->draw( this );
}*/


/*
void Renderer::draw( unsigned int size, GLuint indicesBuffer, GLuint verticesBuffer, GLuint normalsBuffer, GLuint uvsBuffer ) // size is count of indices
{

	// set all uniforms
	glUniform1f ( timeLoc, time );
	glUniformMatrix4fv ( projectionLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
	glUniformMatrix4fv ( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
	glUniformMatrix4fv ( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
	glUniform3fv ( lightLoc, 1, glm::value_ptr( light ) );

	glActiveTexture(  GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, tex0 );
	glUniform1i ( tex0Loc, 0 );

	glActiveTexture(  GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, tex1 );
	glUniform1i ( tex1Loc, 1 );

	glActiveTexture(  GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, tex2 );
	glUniform1i ( tex2Loc, 2 );

	glActiveTexture(  GL_TEXTURE3 );
	glBindTexture( GL_TEXTURE_2D, tex3 );
	glUniform1i ( tex3Loc, 3 );

	// set attributes
	// set indices attribute
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);

	// set vertexattribute
	glEnableVertexAttribArray(verticesLoc); // enable variable
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer); // make vertices the current buffer
	glVertexAttribPointer(verticesLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); // point to bound buffer

	// set normalAttribute
	glEnableVertexAttribArray(normalsLoc);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer); // make vertices the current buffer
	glVertexAttribPointer(normalsLoc, 3, GL_FLOAT, GL_TRUE, 0, 0); // GL_TRUE for nomalisation

	// set uv attribute
	glEnableVertexAttribArray(textureLoc);
	glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer); // make vertices the current buffer
	glVertexAttribPointer(textureLoc, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	// draw indexed arrays
	glDrawElements( GL_TRIANGLES, size, GL_UNSIGNED_INT, (GLvoid*)0 );

	// no current buffer, to avoid mishaps
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glDisableVertexAttribArray( textureLoc );
	glDisableVertexAttribArray( normalsLoc );
	glDisableVertexAttribArray( verticesLoc );
	glBindTexture( GL_TEXTURE_2D, 0 );
}*/


/*********************************************************************************/

// private members
void Renderer::findLocations()
{
	assert ( program != NULL ); // only if there is a program set
	projectionLoc 	= program->getUniformLocation( "projection" );
	viewLoc			= program->getUniformLocation( "view" );
	modelLoc 		= program->getUniformLocation( "model" );
	lightLoc 		= program->getUniformLocation( "light" );
	timeLoc			= program->getUniformLocation( "time" );
	tex0Loc		    = program->getUniformLocation( "tex0" );

	verticesLoc		= program->getAttribLocation( "vertex" );
	normalsLoc		= program->getAttribLocation( "normal" );
	textureLoc 		= program->getAttribLocation( "uv" );
}
