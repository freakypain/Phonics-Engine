#include "Mesh.hpp"
#include "Renderer.hpp"

#include <ios>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <cassert>
#include <map>

#include <glm.hpp>
#include <gl\GL.h>



//Mesh::Mesh() : indicesBuffer(0), verticesBuffer(0), normalsBuffer(0), uvsBuffer(0)
Mesh::Mesh()
{
	//ctor
}

Mesh::~Mesh()
{
	//dtor
}

/*
unsigned int Mesh::size() {
	return indices.size();
}*/

void Mesh::draw( Renderer * aRenderer )
{
	// TODO fix mesh drawing
	//aRenderer->draw( size(), indicesBuffer, verticesBuffer, normalsBuffer, uvsBuffer );
}

/*
std::vector< glm::vec3 > Mesh::getVertices() {
    return vertices;
}*/


// TODO fix mesh loading from file
// static functions
// Load obj file with v/vt/vn


struct faceVert
{
	faceVert() : vert( -1 ), norm( -1 ), coord( -1 ) {}
	int vert;
	int norm;
	int coord;
};

struct vertLess
{
	bool operator() ( const faceVert& lhs, const faceVert& rhs ) const
	{
		if ( lhs.vert != rhs.vert ) return lhs.vert < rhs.vert;
		if ( lhs.norm != rhs.norm ) return lhs.norm < rhs.norm;
		if ( lhs.coord != lhs.coord ) return lhs.coord < rhs.coord;

		return false;
	}
};

/*
Mesh * Mesh::load(const char * filename)
{
	return 0;
}*/

Mesh * Mesh::load( const char * filename )
{

	std::ifstream fstream;
	fstream.open( filename, std::ios_base::in );
	if (!fstream.is_open())	
		std::cout << "Failed to load Mesh" << filename << std::endl;

	// Clear maps
	mPositions.clear();
	mNormals.clear();
	mFaces.clear();

	char *delims = " \n\r";
	char line[500] = { 0 };

	std::vector<Vector3> verts;
	std::vector<Vector3> norms;
	
	std::map<faceVert, int, vertLess> uniqueVertices;
	unsigned int vertCounter = 0;

	while ( fstream.good() )
	{
		memset( (void*)line, 0, 500 );
		fstream.getline( line, 500 );
		
		if ( fstream.eof() )
			break;

		char *nextToken = NULL;
		char *token = strtok_s(line, delims, &nextToken);
		if ( token == NULL || token[0] == '#' || token[0] == '$' )
			continue;


		if ( strcmp(token, "v") == 0 ) 
		{
			float x = 0, y = 0, z = 0, w = 1;
			sscanf_s(line + 2, "%f %f %f %f", &x, &y, &z, &w);
			verts.push_back( Vector3( x / w, y / w, z / w ) );

		} 
		else if ( strcmp(token, "vn") == 0 )
		{
			float x = 0, y = 0, z = 0;
			sscanf_s(line + 3, "%f %f %f", &x, &y, &z);
			norms.push_back( Vector3( x, y, z ) );
		}
		else if ( strcmp( token, "s" ) == 0 ) 
		{
		
		}

		else if ( strcmp( token, "f" ) == 0 ) {
			std::vector<int> vindices;
			std::vector<int> nindices;
			std::vector<int> tindices;

			// fill out a triangle from the line, it could have 3 or 4 edges
			char *lineptr = line + 2;

			while ( lineptr[0] != 0 ) 
			{
				while ( lineptr[0] == ' ' ) 
					++lineptr;

				int vi = 0, ni = 0, ti = 0;

				if ( sscanf_s(lineptr, "%d/%d/%d", &vi, &ni, &ti) == 3 )
				{
					vindices.push_back(vi - 1);
					nindices.push_back(ni - 1);
					tindices.push_back(ti - 1);
				}
				else{
					if ( sscanf_s(lineptr, "%d//%d", &vi, &ni) == 2 )
					{
						vindices.push_back(vi - 1);
						nindices.push_back(ni - 1);
					}
					else{
						if ( sscanf_s(lineptr, "%d/%d", &vi, &ti) == 2 )
						{
							vindices.push_back( vi - 1 );
							tindices.push_back( ti - 1 );
						}
						else{
							if ( sscanf_s(lineptr, "%d", &vi) == 1 ) 
							{
								vindices.push_back( vi - 1 );
							}
						}
					}
				}
				while ( lineptr[0] != ' ' && lineptr[0] != 0 ) 
						++lineptr;
			}


			for ( size_t i = 1; i<vindices.size() - 1; ++i ) 
			{
				Face face;
				faceVert tri;
				tri.vert = vindices[0];

				if ( !nindices.empty() )
					tri.norm = nindices[0];

				if ( !tindices.empty() )
					tri.norm = tindices[0];

				if ( uniqueVertices.count(tri) == 0 )
					uniqueVertices[tri] = vertCounter++;

				face.a = uniqueVertices[tri];
				tri.vert = vindices[i];

				if ( !nindices.empty() )
					tri.norm = nindices[i];

				if ( !tindices.empty() )
					tri.norm = tindices[i];

				if ( uniqueVertices.count(tri) == 0 )
					uniqueVertices[tri] = vertCounter++;

				face.b = uniqueVertices[tri];
				tri.vert = vindices[i + 1];

				if ( !nindices.empty() )
					tri.norm = nindices[i + 1];

				if ( !tindices.empty() )
					tri.norm = tindices[i + 1];

				if ( uniqueVertices.count(tri) == 0 )
					uniqueVertices[tri] = vertCounter++;

				face.c = uniqueVertices[tri];				
				mFaces.push_back(face);
			}
		}

		// Close stream
		fstream.close();

		// Resize instead of reserve
		mPositions.resize( vertCounter );
		if (norms.size() > 0)
			mNormals.resize( vertCounter );
		
		

		std::map<faceVert, int, vertLess>::iterator iter;
		for ( iter = uniqueVertices.begin(); iter != uniqueVertices.end(); ++iter ) 
		{
			mPositions[iter->second] = verts[iter->first.vert];

			if (norms.size() > 0) 
				mNormals[iter->second] = norms[iter->first.norm];			
		}
	}

	return 0;
}

int Mesh::getIndicies() const
{
	return (int)mFaces.size() * 3;
}

int Mesh::getVertices() const
{
	return (int)mPositions.size();
}

const unsigned int* Mesh::getFaces() const
{
	return ( const unsigned int* )&mFaces[0];
}

const float* Mesh::getPositions() const
{
	return (const float*)&mPositions[0];
}

const float* Mesh::getNormals() const
{
	return (const float*)&mNormals[0];
}


/*
Mesh * Mesh::load( const char * fileName )
{
	assert( fileName != 0 );
	assert( strlen( fileName ) > 0 );

	Mesh * mesh = new Mesh();

	std::ifstream file ( fileName, std::ios::in );

	if( file.is_open() ){ // file opened succesfully so it exists
		std::vector<glm::vec3> vertices; // for the indexed data
		std::vector<glm::vec3> normals; // for the indexed data
		std::vector<glm::vec2> uvs; // for the indexed data

		std::map< PackedIndex, unsigned int> keys; // used to convert to indexed arrays

		std::string line; // to store each line in
		while( getline( file, line ) ) { // as long as there are lines to be read
			char cmd[10]; // c-type string to store cmd
			cmd[0] = 0;
			sscanf ( line.c_str(), "%10s", cmd ); // get the first string in the line of max 5 chars (c-style)
			if ( strcmp ( cmd, "v" ) == 0 ) { // line with vertex
				glm::vec3 vertex;
				sscanf( line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z );
				vertices.push_back( vertex );
			} else if ( strcmp ( cmd, "vn" ) == 0 ) { // line with normal
				glm::vec3 normal;
				sscanf( line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z );
				normals.push_back( normal );
			} else if ( strcmp ( cmd, "vt" ) == 0 ) { // line with uv
				glm::vec2 uv;
				sscanf( line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y );
				uvs.push_back( uv );
			} else if ( strcmp ( cmd, "f" ) == 0 ) { // line with face
				glm::ivec3 vertexIndex; // to store the indices
				glm::ivec3 normalIndex;
				glm::ivec3 uvIndex;
				int count = sscanf( line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				//std::cout << line << std::endl;
				if ( count == 10 ) { // there should be 10 args to be read
					for ( int i = 0; i < 3; ++i ) { // make verticesArray out of indexed array
						PackedIndex key (vertexIndex[i], normalIndex[i], uvIndex[i]);
						std::map< PackedIndex, unsigned int>::iterator found = keys.find( key );
						if ( found == keys.end() ) { // key is new
							unsigned int index = keys.size();
							//std::cout << "new i " <<  index << " " << mesh->indices.size() << " : " << vertices[vertexIndex[i]-1] << std::endl;
							keys[ key ] = index;
							mesh->indices.push_back( index );
							mesh->vertices.push_back( vertices[ vertexIndex[i]-1 ] );
							mesh->normals.push_back( normals[ normalIndex[i]-1 ] );
							mesh->uvs.push_back( uvs[ uvIndex[i]-1 ] );
						} else { // key already present
							unsigned int index = found->second;
							//std::cout << "old i " <<  index << " " << mesh->indices.size() << " : " << vertices[vertexIndex[i]-1] << std::endl;
							mesh->indices.push_back( index );
						}
					}
				} else { // something is wrong
					std::cout << "Error reading obj, needing v,vn,vt" << std::endl;
					delete mesh; // free the mem from created body
					return 0; // no body read
				}
			}
		}
		file.close();
		std::cout << "Done loading " << fileName;
		mesh->buffer();
		std::cout << " Done buffering " << std::endl;
		return mesh;
	} else { // file could not be opened;
		std::cout << "Could not read " << fileName << std::endl;
		delete mesh;
		return 0;
	}
}*/

// TODO fix mesh buffer
/*
void Mesh::buffer()
{
	// create vertices buffer
	if ( ! indicesBuffer ) { // if not buffered yet
		glGenBuffers( 1, &indicesBuffer  );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesBuffer  );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW );
		glGenBuffers(1, &verticesBuffer );
			glBindBuffer( GL_ARRAY_BUFFER, verticesBuffer ); // Vertices buffer
			glBufferData( GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0][0], GL_STATIC_DRAW );
		glGenBuffers(1, &normalsBuffer );
			glBindBuffer( GL_ARRAY_BUFFER, normalsBuffer ); // Normals buffer
			glBufferData( GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals[0][0], GL_STATIC_DRAW );
		glGenBuffers(1, &uvsBuffer );
			glBindBuffer( GL_ARRAY_BUFFER, uvsBuffer ); // working on uvs buffer
			glBufferData( GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2), &uvs[0][0], GL_STATIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 ); // important for 2d sfml
	}
}*/

// TODO fix unbuffer
/*
void Mesh::unBuffer()
{
	if ( indicesBuffer ) {
		glDeleteBuffers( 1, & indicesBuffer );
		glDeleteBuffers( 1, & verticesBuffer );
		glDeleteBuffers( 1, & normalsBuffer );
		glDeleteBuffers( 1, & uvsBuffer );
		indicesBuffer = 0;
		verticesBuffer = 0;
		normalsBuffer = 0;
		uvsBuffer= 0;
		std::cout << "Unbuffering" << std::endl;
	}
}*/
