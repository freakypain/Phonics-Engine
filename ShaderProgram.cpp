#include "ShaderProgram.hpp"

#include <iostream>
#include <fstream>

#include "Texture.hpp"
#include <map>
#include <gl\GL.h>

ShaderProgram::ShaderProgram( const char * vertexFileName, const char * fragmentFileName, const char * geometryFileName )
{
	(geometryFileName != NULL) ? load( vertexFileName, fragmentFileName ) : load( vertexFileName, fragmentFileName, geometryFileName );
}

ShaderProgram::~ShaderProgram()
{
	//dtor
}

/*
void ShaderProgram::load(  const char * vertexFileName, const char * fragmentFileName, const char * geometryFileName)
{
	std::string vertexCode   = readFile ( vertexFileName );
	GLuint vertexShaderId   = compileShader( GL_VERTEX_SHADER, vertexCode );

	std::string fragmentCode = readFile ( fragmentFileName );
	GLuint fragmentShaderId = compileShader( GL_FRAGMENT_SHADER, fragmentCode );


    GLuint geometryShaderID = NULL;
	if(geometryFileName != NULL)
    {
         std::string geometryCode = readFile( geometryFileName );
         GLuint geometryShaderID = compileShader(GL_GEOMETRY_SHADER, geometryCode);
    }


	if ( vertexShaderId && fragmentShaderId ) { // all is ok
		id = linkProgram( vertexShaderId, fragmentShaderId, geometryShaderID ); // remember program by id

		glDeleteShader( vertexShaderId );	// free shader resources
		glDeleteShader( fragmentShaderId );	// free shader resources
	} else {
		id = 0; // no program on error
	}
}


GLuint ShaderProgram::getUniformLocation( const char * aName )
{
	return glGetUniformLocation( id, aName );
}
GLuint ShaderProgram::getAttribLocation(  const char * aName  )
{
	return glGetAttribLocation( id, aName );
}

// Set shaderprogram active
void ShaderProgram::use()
{
	glUseProgram( id ); // make this the active shaderprogram
}

void ShaderProgram::draw( unsigned int count )
{
	glDrawElements( GL_TRIANGLES, count, GL_UNSIGNED_INT, (GLvoid*)0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

// private members

// read the shader code into string
std::string ShaderProgram::readFile( const char * fileName )
{
	// Read the Vertex Shader code from the file
	std::string code;
	std::ifstream file ( fileName, std::ios::in);
	if(file.is_open()){
		std::cout << "Reading shader " << fileName << std::endl;
		std::string line = "";
		while(getline(file, line)) { 	// read per line
			code += "\n" + line;		// add to string
		}
		file.close(); // close on finish
	} else {
		std::cout << "Error reading shader " << fileName << std::endl;
		code = "";
	}
	return code;
}

// compile the code, and detect errors.
GLuint ShaderProgram::compileShader( GLenum type, std::string & shaderCode)
{
	std::cout << "Compiling shader " << std::endl;

	// Compile Vertex Shader
	const char * codePointer = shaderCode.c_str();
	GLuint shaderId = glCreateShader( type  ); // get shader id
	glShaderSource( shaderId, 1, &codePointer , NULL );
	glCompileShader( shaderId );

	// Check compiler result
	GLint result = GL_FALSE;
	glGetShaderiv( shaderId, GL_COMPILE_STATUS, &result);

	if ( result ) {
		std::cout << "Shader compiled ok" << std::endl;
		return shaderId;
	} else { // get error message
		int count;
		glGetShaderiv( shaderId, GL_INFO_LOG_LENGTH, &count);
		//std::vector<char> errorMessage( count+1 );
		char errorMessage[ count+1 ];
		glGetShaderInfoLog( shaderId, count, NULL, errorMessage);
		std::cout << errorMessage << std::endl;
		return 0; // no shader id
	}
}

// link the two shaders and return the program id
GLuint ShaderProgram::linkProgram ( GLuint vertexShaderId, GLuint fragmentShaderId, GLuint geometryShaderId )
{
	// Link the program
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	if(geometryShaderId != NULL) glAttachShader(programId, geometryShaderId);

	glLinkProgram(programId);

	ShaderProgram::setProgramID(programId);

	// Check the program
	GLint result = GL_FALSE;
	glGetProgramiv( programId, GL_LINK_STATUS, &result );
	if ( result ) {
		std::cout << "program linked ok" << std::endl;
		return programId;
	} else { // error, show message
		int count;
		glGetProgramiv( programId, GL_INFO_LOG_LENGTH, &count );
		//std::vector<char> ProgramErrorMessage( max(count, int(1)) );
		char errorMessage[ count+1 ];
		glGetProgramInfoLog( programId, count, NULL, errorMessage );
		std::cout << errorMessage << std::endl;
		return 0;
	}
}

void ShaderProgram::setProgramID(GLuint aProgramID){
    id = aProgramID;
}


GLuint ShaderProgram::getProgramID(){
    return id;
}

void ShaderProgram::setUniform(const std::string& aName, const int aId)
{
    GLuint location = getUniformLoc(aName);
    glUniform1i(location, aId);
}

void ShaderProgram::setUniform4x4(const std::string& aName, const float* aMatrix, bool aTranspose)
{
    GLuint location = getUniformLoc(aName);
    glUniformMatrix4fv(location, 1, aTranspose, aMatrix);
}

void ShaderProgram::setUniform3x3(const std::string& aName, const float* aMatrix, bool aTranspose)
{
    GLuint location = getUniformLoc(aName);
    glUniformMatrix3fv(location, 1, aTranspose, aMatrix);
}

void ShaderProgram::setUniform(const std::string& aName, const float aRed, const float aGreen, const float aBlue, const float aAlpha)
{

    GLuint location = getUniformLoc(aName);
    glUniform4f(location, aRed, aGreen, aBlue, aAlpha);
}

void ShaderProgram::setUniform(const std::string& aName, const float aX, const float aY, const float aZ)
{
    GLuint location = getUniformLoc(aName);
    glUniform3f(location, aX, aY, aZ);
}

void ShaderProgram::setUniform(const std::string& aName, const float aScalar)
{
    GLuint location = getUniformLoc(aName);
    glUniform1f(location, aScalar);
}

GLuint ShaderProgram::getUniformLoc(const std::string& aName)
{
    std::map<std::string, GLuint>::iterator i = uniformMap.find(aName);
    if (i == uniformMap.end())
    {
        GLuint location = glGetUniformLocation(id, aName.c_str());
        uniformMap.insert(std::make_pair(aName, location));
        return location;
    }

    return (*i).second;
}*/




