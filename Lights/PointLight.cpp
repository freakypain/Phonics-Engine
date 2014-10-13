#include "PointLight.hpp"
#include "../Vector3.hpp"

PointLight::PointLight( Colour colour, Vector3 position )	: Light( LIGHT_POINT, colour ), mPosition( position ),	mAttenuationConstant( 0.0f ),	mAttenuationLinear( 1.0f ), mAttenuationQuadratic( 0.0f )
{
}

PointLight::PointLight( Colour colour, Vector3 position, float attentConst, float attenLinear, float attenQuadratic ) : Light( LIGHT_POINT, colour ),
														mPosition( position ), mAttenuationConstant( attentConst ), mAttenuationLinear( attenLinear ), mAttenuationQuadratic( attenQuadratic )
{

}

PointLight::~PointLight()
{

}


Vector3 PointLight::getPosition() const
{
	return mPosition;
}

float PointLight::getAttenuation( float distance )
{
	if ( distance < mRange )
	{
		return 1 / ( mAttenuationConstant + ( mAttenuationLinear * distance ) + ( mAttenuationQuadratic * ( distance * distance ) ) );
	}
	else
	{
		return 0;
	}
}

Colour PointLight::calcuatePrimitveLightAtPoint( Primitive& primitive, Vector3& intersectionPoint )
{
	return Colour();
}

/*
Colour PointLight::calcuatePrimitveLightAtPoint( GameObject& gameObject, Vector3& intersectionPoint )
{
	return Colour();
}*/




