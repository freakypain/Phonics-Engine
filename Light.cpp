#include <iostream>
#include <string>
#include "Light.hpp"


// TODO fix light on GameObject
/*
Light::Light(GameObject * aParent) : parent( aParent )
{
}*/

Light::Light( LightType type = LIGHT_NONE, Colour colour = Colour() ) : mLightType( type ), mColour( colour ) 
{


}

Light::~Light()
{
	//dtor
}

Colour Light::getColour()
{
	return mColour;
}

LightType Light::getType()
{
	return mLightType;
}
