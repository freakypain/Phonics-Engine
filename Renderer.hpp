#ifndef RENDERER_H
#define RENDERER_H

#include <Windows.h>
#include <gl\GL.h>
#include <glm.hpp>

#include "RenderPoint.hpp"
#include "Ray.hpp"
#include "Colour.hpp"

class ShaderProgram;
class Texture;
class GameObject;
class Texture;
class Scene;


class Renderer
{

	public:
		Renderer(RenderPoint* renderTarget);
		~Renderer();

		Scene* getScene();
		Colour	sendRay(Ray& ray, int traceDepth);
		ShaderProgram * getShaderProgram();

		void	initialize();
		
		bool	draw();
		//void draw(GameObject * aWorld); // starting point for drawing
		//void draw(unsigned int size, GLuint indicesId, GLuint verticesId, GLuint normalsId, GLuint uvsId); // drawing mesh, all other uniforms etc should be allready available
		void setProjection(glm::mat4 aProjection);
		void setView(glm::mat4 aView);
		void setModel(glm::mat4 aModel);
		void setShader(ShaderProgram * aShader);
		void setTime(float aTime);
		void setLight(glm::vec3 aLight);
		void setTexture(Texture * texture);
	

	protected:
		float			mViewPlaneX1, mViewPlaneX2, mViewPlaneY1, mViewPlaneY2;
		float			mDeltaX, mDeltaY;
		float			mCurrentX, mCurrentY;
		int				mNextLine, mBufferIndex;
		RenderPoint*	mRenderTarget;
		Scene*			mScene;
		ShaderProgram * program;	
		Vector3			mEyePosition;

	private:
		// shader input locations
		//GLuint projectionLoc, viewLoc, modelLoc, lightLoc, timeLoc; 	// uniform locations
		//GLuint verticesLoc, normalsLoc, textureLoc;		// attribute locations
		//GLuint tex0Loc;

		// buffered variables
		float time;

		glm::mat4 projection, view, model;
		glm::vec3 light;
		GLuint mTexture;

		void findLocations();
};

#endif // RENDERER_H
