#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Time.hpp"
#include "External\stb_image.h"

#include <iostream>
#include <memory>
#include <glm.hpp>
#include <gl\GL.h>

std::map< const char *, Texture * > Texture::mTextures; // for static textures

Texture::Texture( const char * filename ) : mFilename( filename )
{
	//ctor
}

Texture::~Texture()
{
	glDeleteTextures(1, &mTextureID);  // free gpu memory
}

Texture * Texture::load( const char* filename )
{
	// Check if image already has been loaded
	std::map< const char*, Texture* >::iterator textureIterator = mTextures.find(filename);
	if ( textureIterator != mTextures.end() )
		return textureIterator->second;
	
	// Load image from file
	int width, height, comp;	
	unsigned char* data = stbi_load(filename, &width, &height, &comp, 4); 

	if ( data == NULL )
		return 0;
		
	std::unique_ptr<Texture> texture{new Texture( filename )};

	glGenTextures(1, &texture->mTextureID);
	glBindTexture(GL_TEXTURE_2D, texture->mTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free( data );

	mTextures[filename] = texture.get();

	return texture.get();
}

GLuint Texture::getId() const 
{
	return mTextureID;
}