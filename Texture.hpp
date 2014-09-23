#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION // STB image loading

#include <glm.hpp>
#include <map>
#include <gl\GL.h>


class Mesh;
class ShaderProgram;


class Texture
{
	private:
		const char * mFilename;
		GLuint mTextureID; // OpenGL id for texture buffer
		static std::map< const char*, Texture* > mTextures; //all previously loaded meshes;

	private:
		Texture( const char* filename );

	public:
		static Texture * load( const char* filename ); 
		virtual ~Texture();
		GLuint getID() const;

};

#endif // TEXTURE_H
