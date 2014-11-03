#include "Sphere.hpp"
#include "../Math/Vector3.hpp"


Sphere::Sphere( Material material, Vector3& center, float radius, bool shadow = true ) 
	: Primitive( material, shadow ), mCenter( center ), mRadiusSquared( radius * radius ), mRadius( radius ), mOneOverRadius( 1.0f / radius )
{

}

Sphere::~Sphere()
{

}

// Return Center of primitive
Vector3& Sphere::getCenter()
{
	return mCenter;
}

Vector3 Sphere::getNormal( Vector3& position )
{
	return (position - mCenter) * mOneOverRadius;
}

// Intersection between ray and sphere
bool Sphere::intersect( Ray& ray, float& distance )
{
	bool intersect = false;

	Vector3 l = mCenter - ray.getOrigin();
	float scalar = Vector3::dot( ray.getDirection(), l );

	float f = mRadiusSquared - Vector3::dot( l, l ) + ( scalar * scalar );

	if ( f < 0.0f )
	{
		return intersect;
	}
	else{
		float a = scalar - sqrtf(f);

		if ( a > 0.1f && a < MAXDISTANCE )
		{
			distance = a;
			intersect = true;
		}
	}

	return intersect;
}




