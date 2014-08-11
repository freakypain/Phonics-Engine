#ifndef RAY_H
#define RAY_H

#include "Vector3.hpp"

class Ray
{
public:
	Ray();
	Ray( Vector3& origin, Vector );

	Vector3& getOrigin		{ return mOrigin    };
	Vector3& getDirection	{ return mDirection };

private:
	Vector3 mOrigin;
	Vector3 mDirection;
};

#endif // RAY_H

