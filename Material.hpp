#ifndef MATERIAL_H
#define MATERIAL_H

#include "Colour.hpp"


struct Material
{
	Colour mDiffuse;
	float mDiffuseFactor;
	float mReflection;
	float mSpecular;

	Material(Colour diffuse = Colour(), float diffuseFac = 0.5f, float reflection = 0.5f, float specular = 0.5f);
	~Material();
};

#endif

