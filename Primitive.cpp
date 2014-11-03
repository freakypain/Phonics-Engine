#include "Primitive.hpp"
#include "Math/Vector3.hpp"
#include "Colour.hpp"


Primitive::Primitive( Material material, bool castShadow = true ) : mCastShadows( castShadow ), mMaterial( material )
{

}

Primitive::~Primitive()
{

}

// Get Normal
Material* Primitive::getMaterial()
{
	return &mMaterial;
}

// Get Colour
Colour Primitive::getColour( Vector3& ) const
{
	return mMaterial.mDiffuse;
}

// Return Shadow
bool Primitive::getShadow()
{
	return mCastShadows;
}