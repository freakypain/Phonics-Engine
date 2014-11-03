#ifndef LIGHT_H
#define LIGHT_H

#include "Math/Vector3.hpp"
#include "GameObject.hpp"
#include "Colour.hpp"
#include "Renderer.hpp"
#include "Primitive.hpp"

enum  LightType
{
	LIGHT_NONE,
	LIGHT_POINT,
	LIGHT_DIRECTIONAL,
	LIGHT_SPOT,
};


class Light
{
	public:
		// TODO fix light on GameObject
		//Light(GameObject * aParent);
		Light( LightType type, Colour colour );
		virtual ~Light();

		LightType getType();
		Colour getColour();

		virtual Colour calcuatePrimitveLightAtPoint( Primitive& primitive, Vector3& intersectionPoint ) = 0; // Calucate Light Angle

		
    protected:
        GameObject * parent;

	private:
		LightType mLightType;
		Colour mColour;
};

#endif // LIGHT_H
