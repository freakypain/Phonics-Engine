#ifndef PLANE_H
#define PLANE_H

#include "../Primitive.hpp"

class Plane : public Primitive
{
	public:
		Plane( Material material, Vector3& normal, float distance, bool shadow );
		~Plane();

		Vector3 getNormal( Vector3& position );
		bool Plane::intersect( Ray& ray, float& distance );

	private:
		Vector3 mNormal;
		float mDistance;
};


#endif

