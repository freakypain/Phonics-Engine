// External
#include <Windows.h>
#include <iostream>
#include <glew.h>
#include <gtc\type_ptr.hpp>
#include <glm.hpp>

// Internal
#include "Renderer.hpp"
#include "ShaderProgram.hpp"
#include "GameObject.hpp"
#include "Texture.hpp"
#include "Time.hpp"
#include "Scene.hpp"



Renderer::Renderer(RenderPoint* renderPoint)
{
	mScene = new Scene();
	mRenderTarget = renderPoint;
}

Renderer::~Renderer()
{
	delete mScene;
}



// Return intersection point
Colour Renderer::sendRay(Ray& ray, int traceDepth)
{
	if (traceDepth > MAXTRACEDEPTH)
		return Colour();

	Colour		litColour, reflectedColour;
	float		distanceToIntersect = MAXDISTANCE;	// Ignore primitives beyond this
	Vector3		intersectionPoint;
	Primitive*	nearestPrimitive = 0;

	nearestPrimitive = mScene->getFirstPrimitive(ray, distanceToIntersect);

	if (!nearestPrimitive)
		return Colour();

	else
	{
		// Hit a primitive, calculate lighting
		intersectionPoint = ray.getOrigin() + ray.getDirection() * distanceToIntersect;
		litColour = mScene->calcuatePrimiateLightingAtPoint((*nearestPrimitive), intersectionPoint, ray.getDirection());

		// Calculate reflection
		float reflectionFactor = nearestPrimitive->getMaterial()->mReflection;

		if (reflectionFactor > 0.0f)
		{
			Vector3 normal = nearestPrimitive->getNormal(intersectionPoint);
			Vector3 reflected = ray.getDirection() - normal * (2.0f * Vector3::dot(ray.getDirection(), normal));

			Ray reflectedRay = Ray(intersectionPoint + reflected * 0.0001f, reflected);
			reflectedColour = sendRay(reflectedRay, traceDepth + 1) * reflectionFactor;
		}

		return litColour + reflectedColour;
	}
}

// Draw one line at the time
bool Renderer::draw()
{
	// Render remaining horizontal lines
	for (int y = mNextLine; y < mRenderTarget->getHeight(); y++)
	{
		// Start interpolating from left side of view plane
		mCurrentX = mViewPlaneX1;

		// Render all pixels on the current line
		for (int x = 0; x < mRenderTarget->getWidth(); x++)
		{
			// Create a ray from the origin towards current 'pixel'
			Vector3 direction = Vector3(mCurrentX, mCurrentY, 0) - mEyePosition;
			direction.normalize();
			Ray ray(mEyePosition, direction);

			// Find the closest primitive and its distance/colour
			Colour pixelColour = sendRay(ray, 1);

			// Convert and pack RGB values into a pixel for the buffer
			mRenderTarget->setPixel(mBufferIndex++, pixelColour.createPixel());

			// Move to next 'pixel' on the view plane
			mCurrentX += mDeltaX;
		}

		// Move to next line of 'pixels' on the view plane
		mCurrentY += mDeltaY;

		// Note which line should start the next loop
		mNextLine = y + 1;

		// Exit briefly to allow Draw() to paint the screen
		return false;
	}

	return true;
}


// Reset count and buffer pixel index. Setup camera. Defines view plane and x/y delate values for interpolation
void Renderer::initialize()
{
	// Reset current line and buffer (current pixel) index
	mNextLine = mBufferIndex = 0;

	// Camera/view position from which rays will be cast
	mEyePosition = Vector3(0, 0, -5);

	// View plane in world coordinates (based on screen aspect ratio - 16:10)
	mViewPlaneX1 = -8;
	mViewPlaneX2 = 8;
	mViewPlaneY1 = mCurrentY = 5;
	mViewPlaneY2 = -5;

	// Delta values used for interpolating along the view plane
	mDeltaX = (mViewPlaneX2 - mViewPlaneX1) / mRenderTarget->getWidth();
	mDeltaY = (mViewPlaneY2 - mViewPlaneY1) / mRenderTarget->getHeight();
}

// TODO Fix set Shaders
void Renderer::setShader( ShaderProgram * aProgram )
{
	program = aProgram;
	//program->use(); // this is the default program
	//findLocations(); // find where to put the uniforms to
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


void Renderer::setTexture( Texture * texture ) // for single texture at a time, otherwise use activeTexture
{
	mTexture = texture->getID();
}

void Renderer::setTime( float aTime )
{
	time = aTime; // set time for use in vs and fs
}

ShaderProgram * Renderer::getShaderProgram()
{
    return program;
}


Scene* Renderer::getScene()
{
	return mScene;
}

// TODO Fix DRAW to render GameObjects
/*
void Renderer::draw(GameObject * aWorld)
{

}*/
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

// TODO FIX Renderer
/*
void Renderer::draw(unsigned int size, GLuint indicesBuffer, GLuint verticesBuffer, GLuint normalsBuffer, GLuint uvsBuffer) // size is count of indices
{
	
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


	// set attributes
	// set indices attribute
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);

	// set vertexattribute
	glEnableVertexAttribArray( verticesLoc ); // enable variable
	glBindBuffer( GL_ARRAY_BUFFER, verticesBuffer ); // make vertices the current buffer
	glVertexAttribPointer( verticesLoc, 3, GL_FLOAT, GL_FALSE, 0, 0 ); // point to bound buffer

	// set normalAttribute
	glEnableVertexAttribArray( normalsLoc );
	glBindBuffer( GL_ARRAY_BUFFER, normalsBuffer ); // make vertices the current buffer
	glVertexAttribPointer( normalsLoc, 3, GL_FLOAT, GL_TRUE, 0, 0 ); // GL_TRUE for nomalisation

	// set uv attribute
	glEnableVertexAttribArray( textureLoc );
	glBindBuffer( GL_ARRAY_BUFFER, uvsBuffer ); // make vertices the current buffer
	glVertexAttribPointer( textureLoc, 2, GL_FLOAT, GL_FALSE, 0, 0 );

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
/*
void Renderer::findLocations()
{
	assert ( program != 0 ); // only if there is a program set
	projectionLoc 	= program->getUniformLocation( "projection" );
	viewLoc			= program->getUniformLocation( "view" );
	modelLoc 		= program->getUniformLocation( "model" );
	lightLoc 		= program->getUniformLocation( "light" );
	timeLoc			= program->getUniformLocation( "time" );
	tex0Loc		    = program->getUniformLocation( "tex0" );

	verticesLoc		= program->getAttribLocation( "vertex" );
	normalsLoc		= program->getAttribLocation( "normal" );
	textureLoc 		= program->getAttribLocation( "uv" );
}*/