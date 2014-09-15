#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Colour.hpp"

class Primitive
{
	public:
		Primitive( bool castShadow );
		~Primitive();

		bool castShow();
		//virtual Colour getColour( Vector3& ) const;
		virtual Vector3 getNormal( Vector3& position ) = 0;

		virtual bool intersect( Ray& ray, float& distance ) = 0;

	protected:
		bool mCastShadows;
};

#endif

