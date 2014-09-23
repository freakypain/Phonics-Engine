#ifndef MATERIAL_H
#define MATERIAL_H


#include "Colour.hpp"

struct Material
{
	Colour diffuse;
	float diffuseFactor;
	float reflection;
	float specular;

	// Default Constructor
	Material(Colour diffuse = Colour(), float refulection = 0.5f, float diffuseFac = 0.5f, float specular = 1.5f) 
			: diffuse(diffuse), diffuseFactor(diffuseFac), specular(specular)
	{

	}

};

#endif

