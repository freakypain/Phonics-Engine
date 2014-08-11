#ifndef RENDERER_H
#define RENDERER_H

#include "RenderPoint.hpp"
#include "Ray.hpp"
#include "stdafx.h"

#include <gl\GL.h>


class ShaderProgram;
class Texture;
class GameObject;

class Renderer
{
    protected:
        // the shader wrapper
        ShaderProgram * program;
		float			mViewPlaneX1, mViewPlaneX2, mViewPlaneY1, mViewPlaneY2;
		float			mDeltaX, mDeltaY;
		float			mCurrentX, mCurrentY;
		RenderPoint*	mRenderPoint;
		//Scene*			mScene;
		int				mNextLine;
		int				mBufferIndex;
		Vector3			mEyePosition;
		
	private:
		// shader input locations
		GLuint projectionLoc, viewLoc, modelLoc, lightLoc, timeLoc, animationLoc, spriteWidthLoc; 	// uniform locations
		GLuint verticesLoc, normalsLoc, textureLoc;		// attribute locations
		GLuint tex0Loc;


		// buffered variables
		float time;
		glm::mat4 projection, view, model;
		glm::vec3 light;
		GLuint tex0;



	public:
		Renderer( RenderPoint * renderPoint );
		virtual ~Renderer( );

        void setProjection( glm::mat4 aProjection );
        void setView( glm::mat4 aView );
        void setModel( glm::mat4 aModel );
        void setShader(ShaderProgram * aShader);

        ShaderProgram * getShaderProgram();

		void setTime( float aTime );
		void setLight( glm::vec3 aLight );
		void setTexture0 ( Texture * tex0 );

		//void draw( GameObject * aWorld ); // starting point for drawing
		//void draw( unsigned int size, GLuint indicesId, GLuint verticesId, GLuint normalsId, GLuint uvsId ); // drawing mesh, all other uniforms etc should be allready available
		bool draw();

	private:
		void findLocations();
};

#endif // RENDERER_H
