#include "Ray.hpp"

Ray::Ray(void) : mOrigin( Vector3( 0, 0, 0 )), mDirection( Vector3( 0, 0, 0 )) {};
Ray::Ray(Vector3& origin, Vector3& direction) : mOrigin(origin), mDirection(direction) {}