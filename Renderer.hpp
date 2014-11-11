#ifndef RENDERER_H
#define RENDERER_H

// External
#include <Windows.h>
#include <gl\GL.h>

// Internal
#include "RenderPoint.hpp"
#include "Ray.hpp"
#include "Colour.hpp"

// Math
#include "Math\Matrix3.hpp"
#include "Math\Vector3.hpp"

class GameObject;
class Scene;


class Renderer
{

	public:
		Renderer(RenderPoint* renderTarget);
		~Renderer();

		Colour	sendRay(Scene& scene, Ray& ray, int traceDepth);

		void	initialize();
		
		bool draw( Scene&  scene );
		//void draw(GameObject * aWorld); // starting point for drawing
		//void draw(unsigned int size, GLuint indicesId, GLuint verticesId, GLuint normalsId, GLuint uvsId); // drawing mesh, all other uniforms etc should be allready available
		void setProjection(Matrix4 aProjection);
		void setView(Matrix4 aView);
		void setModel(Matrix4 aModel);
		void setTime(float aTime);
		void setLight(Vector3 aLight);
	

	protected:
		float			mViewPlaneX1, mViewPlaneX2, mViewPlaneY1, mViewPlaneY2;
		float			mDeltaX, mDeltaY;
		float			mCurrentX, mCurrentY;
		int				mNextLine, mBufferIndex;
		RenderPoint*	mRenderTarget;
		Vector3			mEyePosition;

	private:
		// buffered variables
		float time;

		Matrix4 projection, view, model;
		Vector3 light;	

		void findLocations();
};

#endif // RENDERER_H
