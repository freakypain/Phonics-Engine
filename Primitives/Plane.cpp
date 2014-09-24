#include "Plane.hpp"

Plane::Plane( Material material, Vector3& normal, float distance, bool shadow ) 
	: Primitive( material, shadow ), mNormal( normal ), mDistance( distance )
{

}

Plane::~Plane()
{

}

// Return Normal
Vector3 Plane::getNormal( Vector3& position )
{
	return mNormal;
}

// Intersect between plane & ray
// Return 1 == hit, 0 == miss and dstiance from eye to intersect
bool Plane::intersect( Ray& ray, float& distance )
{
	bool intersect = false;

	float dotPlane = Vector3::dot( mNormal, ray.getDirection() );
	
	if (dotPlane < 0)
	{
		float distToIntersect = -( Vector3::dot( ray.getOrigin(), mNormal ) + mDistance ) / dotPlane;
		if ( distToIntersect < MAXDISTANCE )
		{
			distance = distToIntersect;
			intersect = true;
		}
	}

	return intersect;
}

