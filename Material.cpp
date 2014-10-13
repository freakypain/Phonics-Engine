#include "Material.hpp"
#include "Colour.hpp"

// Default Constructor
Material::Material( Colour diffuse, float diffuseFac, float reflection, float specular )
	: mDiffuse( diffuse ), mDiffuseFactor( diffuseFac ), mReflection( reflection ), mSpecular( specular )
{

}

Material::~Material()
{

}