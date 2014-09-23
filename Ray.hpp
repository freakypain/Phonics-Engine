#ifndef RAY_H
#define RAY_H

#include "Vector3.hpp"

class Ray
{
	public:
		Ray();
		Ray( const Vector3& origin, const Vector3& direction );
		//~Ray() = default;
		~Ray();


		Vector3& getOrigin();
		Vector3& getDirection();

	private:
		Vector3 mOrigin;
		Vector3 mDirection;
};

#endif // RAY_H

