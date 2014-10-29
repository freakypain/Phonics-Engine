// External
#include <Windows.h>
#include <iostream>
#include <glew.h>
#include <gtc\type_ptr.hpp>
#include <glm.hpp>

// Internal
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Time.hpp"
#include "Scene.hpp"



Renderer::Renderer(RenderPoint* renderPoint)
{
	//mScene = new Scene();
	mRenderTarget = renderPoint;
}

Renderer::~Renderer()
{

}



// Return intersection point
Colour Renderer::sendRay(Scene& scene, Ray& ray, int traceDepth)
{
	if (traceDepth > MAXTRACEDEPTH)
		return Colour();

	Colour		litColour, reflectedColour;
	float		distanceToIntersect = MAXDISTANCE;	// Ignore primitives beyond this
	Vector3		intersectionPoint;
	Primitive*	nearestPrimitive = 0;

	nearestPrimitive = scene.getFirstPrimitive(ray, distanceToIntersect);

	if (!nearestPrimitive)
		return Colour();

	else
	{
		// Hit a primitive, calculate lighting
		intersectionPoint = ray.getOrigin() + ray.getDirection() * distanceToIntersect;
		litColour = scene.calcuatePrimiateLightingAtPoint((*nearestPrimitive), intersectionPoint, ray.getDirection());

		// Calculate reflection
		float reflectionFactor = nearestPrimitive->getMaterial()->mReflection;

		if (reflectionFactor > 0.0f)
		{
			Vector3 normal = nearestPrimitive->getNormal(intersectionPoint);
			Vector3 reflected = ray.getDirection() - normal * (2.0f * Vector3::dot(ray.getDirection(), normal));

			Ray reflectedRay = Ray(intersectionPoint + reflected * 0.0001f, reflected);
			reflectedColour = sendRay(scene, reflectedRay, traceDepth + 1) * reflectionFactor;
		}

		return litColour + reflectedColour;
	}
}

// Draw one line at the time
bool Renderer::draw( Scene& scene )
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
			Colour pixelColour = sendRay(scene, ray, 1);

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

void Renderer::setTime( float aTime )
{
	time = aTime; // set time for use in vs and fs
}