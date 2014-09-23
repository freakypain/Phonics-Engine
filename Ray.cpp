#include "Ray.hpp"

Ray::Ray() : mOrigin( Vector3( 0, 0, 0 )), mDirection( Vector3( 0, 0, 0 )) 
{

}

Ray::Ray( const Vector3& origin, const Vector3& direction ) : mOrigin( origin ), mDirection( direction )
{ 

}

Ray::~Ray()
{

}

Vector3& Ray::getOrigin()
{ 
	return mOrigin;    
}

Vector3& Ray::getDirection()
{ 
	return mDirection; 
}