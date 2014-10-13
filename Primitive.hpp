#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Colour.hpp"
#include "Material.hpp"

class Primitive
{
	public:
		Primitive( Material material, bool castShadow );
		~Primitive();

		bool getShadow();

		Material* getMaterial();
		virtual Colour getColour( Vector3& ) const;
		virtual Vector3 getNormal( Vector3& position ) = 0;
		virtual bool intersect( Ray& ray, float& distance ) = 0;

	protected:
		Material mMaterial;
		bool mCastShadows;
};

#endif // PRIMITIVE_H

