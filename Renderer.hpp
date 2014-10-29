#ifndef RENDERER_H
#define RENDERER_H

#include <Windows.h>
#include <gl\GL.h>
#include <glm.hpp>

#include "RenderPoint.hpp"
#include "Ray.hpp"
#include "Colour.hpp"

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
		void setProjection(glm::mat4 aProjection);
		void setView(glm::mat4 aView);
		void setModel(glm::mat4 aModel);
		void setTime(float aTime);
		void setLight(glm::vec3 aLight);
	

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

		glm::mat4 projection, view, model;
		glm::vec3 light;	

		void findLocations();
};

#endif // RENDERER_H
