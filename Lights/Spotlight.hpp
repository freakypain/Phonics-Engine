#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "../Colour.hpp"
#include "../Light.hpp"
#include "../Math/Vector3.hpp"



class Spotlight : public Light{
    public:
        //Spotlight( GameObject * aParent );
		Spotlight(Colour colour, Vector3 position);
		Spotlight(Colour colour, Vector3 position, float attentConst, float attenLinear, float attenQuadratic);

		~Spotlight();       


		float getAttenuation(float distance);
		Vector3 getPosition() const;

		virtual Colour calcuatePrimitveLightAtPoint(Primitive& primitive, Vector3& intersectionPoint); // Calucate Light Angle Primitive
		virtual Colour calcuatePrimitveLightAtPoint(GameObject& gameObject, Vector3& intersectionPoint); // Calucate Light Angle GameObject

	private:
		Vector3 mPosition;
		float mRange;
		float mAttenuationConstant;
		float mAttenuationLinear;
		float mAttenuationQuadratic;
};


#endif // SPOTLIGHT_H
