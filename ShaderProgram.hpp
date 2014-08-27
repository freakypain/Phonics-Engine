#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <Windows.h>
#include <map>
#include <string>
#include <gl\GL.h>


class Texture;
class GameObject;

class ShaderProgram
{
	protected:
        GLuint* programID;

	public: // var locations
		GLuint id;

	public: // functions
		ShaderProgram( const char * vertexFileName, const char * fragmentFileName, const char * geometryFileName = 0);
		virtual ~ShaderProgram();

		/*
		void load( const char * vertexFileName, const char * fragmentFileName, const char * geometryFileName = 0 ); // loads, compiles and links the shaders

		GLuint getUniformLocation( const char * name );
		GLuint getAttribLocation(  const char * name  );

		void setProgramID(GLuint aProgramID);
		GLuint getProgramID();

		void use();

		void draw( unsigned int count );

        // Set uniforms
		void setUniform			( const std::string& aName, const int id );
        void setUniform4x4		( const std::string& aName, const float* aMatrix, bool transpose=false );
        void setUniform3x3		( const std::string& aName, const float* aMatrix, bool transpose=false );
        void setUniform			( const std::string& aName, const float aRed, const float aGreen, const float aBlue, const float aAlpha );
        void setUniform			( const std::string& aName, const float aX, const float aY, const float aZ );
        void setUniform			( const std::string& aName, const float aScalar );
        GLuint getUniformLoc	( const std::string& name );
        std::map<std::string, GLuint> uniformMap;

	private: // functions
		std::string readFile	( const char * filePath );
		GLuint compileShader	( GLenum type, std::string & shaderCode );
		GLuint linkProgram		( GLuint vertexShaderId, GLuint fragmentShaderId, GLuint geometryShaderId = 0 );
		void getLocations();*/
};

#endif // SHADERPROGRAM_H

