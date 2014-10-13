#ifndef POINTLIGHT_H
#define POINT_LIGHT

#include "../Light.hpp"



class PointLight : public Light
{
	public:
		PointLight( Colour colour, Vector3 position );
		PointLight( Colour colour, Vector3 position, float attentConst, float attenLinear, float attenQuadratic );
		virtual ~PointLight();

		float getAttenuation( float distance );
		Vector3 getPosition() const;
		virtual Colour calcuatePrimitveLightAtPoint( Primitive& primitive, Vector3& intersectionPoint ); // Calucate Light Angle Primitive
		//virtual Colour calcuatePrimitveLightAtPoint( GameObject& gameObject, Vector3& intersectionPoint ); // Calucate Light Angle GameObject

	private:
		Vector3 mPosition;
		float mRange;
		float mAttenuationConstant;
		float mAttenuationLinear;
		float mAttenuationQuadratic;

};


#endif //POINTLIGHT_H

