#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <vector>
#include "glm.hpp"
#include <map>

class Texture;

class ShaderProgram
{
    protected:
        GLuint * programID;

	public: // var locations
		GLuint id;

	public: // functions
		ShaderProgram( const char * vertexFileName, const char * fragmentFileName, const char * geometryFileName = NULL);
		virtual ~ShaderProgram();

		void load( const char * vertexFileName, const char * fragmentFileName, const char * geometryFileName = NULL ); // loads, compiles and links the shaders

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
		GLuint linkProgram		( GLuint vertexShaderId, GLuint fragmentShaderId, GLuint geometryShaderId = NULL );
		void getLocations();
};

#endif // SHADERPROGRAM_H

