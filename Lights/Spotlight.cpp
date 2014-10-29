#include <iostream>
#include "Spotlight.hpp"
#include "../Light.hpp"
#include "../GameObject.hpp"
#include "../Renderer.hpp"


Spotlight::Spotlight(Colour colour, Vector3 position) : Light(LIGHT_POINT, colour), mPosition(position), mAttenuationConstant(0.0f), mAttenuationLinear(1.0f), mAttenuationQuadratic(0.0f)
{
}

Spotlight::Spotlight(Colour colour, Vector3 position, float attentConst, float attenLinear, float attenQuadratic) : Light(LIGHT_POINT, colour),
mPosition(position), mAttenuationConstant(attentConst), mAttenuationLinear(attenLinear), mAttenuationQuadratic(attenQuadratic)
{

}


Spotlight::~Spotlight()
{

}

Vector3 Spotlight::getPosition() const
{
	return mPosition;
}

float Spotlight::getAttenuation(float distance)
{
	if (distance < mRange)
	{
		return 1 / (mAttenuationConstant + (mAttenuationLinear * distance) + (mAttenuationQuadratic * (distance * distance)));
	}
	else
	{
		return 0;
	}
}

Colour Spotlight::calcuatePrimitveLightAtPoint(Primitive& primitive, Vector3& intersectionPoint)
{
	return Colour();
}

Colour Spotlight::calcuatePrimitveLightAtPoint(GameObject& gameObject, Vector3& intersectionPoint)
{
	return Colour();
}