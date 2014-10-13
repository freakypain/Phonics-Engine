#ifndef SPHERE_H
#define SPHERE_H

#include "../Primitive.hpp"
#include "../Vector3.hpp"


class Sphere : public Primitive{

	public:
		Sphere( Material material, Vector3& center, float radius, bool shadow );
		~Sphere();

		Vector3&	getCenter();				
		Vector3		getNormal( Vector3& position );

		bool intersect( Ray& ray, float& distance );

	private:
		Vector3 mCenter;
		float mRadius;
		float mRadiusSquared;
		float mOneOverRadius;


};

#endif

