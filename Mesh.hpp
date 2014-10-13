#ifndef MESH_H
#define MESH_H

#include <Windows.h>
#include <iostream>
#include <vector>
#include "Vector3.hpp"


#include <gtc\matrix_transform.hpp>
#include <gl\GL.h>

class Renderer;

struct Face
{
	int a,b,c;
};

class Mesh
{

	public: // functions
		Mesh();
		virtual ~Mesh();

		// TODO fix it static
		//static Mesh * load( const char * fileName ); 
		Mesh * load(const char * fileName);

		//std::vector<glm::vec3> getVertices();

		//unsigned int size();

		void draw( Renderer * aRenderer );

		int getIndicies() const;
		int getVertices() const;
		const unsigned int* getFaces() const;
		const float* getPositions() const ;
		const float* getNormals() const;
		
	private:
		std::vector<Face> mFaces;
		std::vector<Vector3> mPositions;
		std::vector<Vector3> mNormals;

//https://github.com/tamato/simple-obj-loader/blob/master/objloader.h , E:\Downloads\simple-obj-loader-master\simple-obj-loader-master

		void buffer();
		void unBuffer();


};

#endif // MESH_H
