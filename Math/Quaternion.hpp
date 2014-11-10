#ifndef QUATERNION_H
#define QUATERNION_H

// Internal
#include "../Math.hpp"
#include "Vector3.hpp"

class Quaternion : public Math
{
		
public:
	Quaternion( float x, float y, float z, float w );
	~Quaternion();

	float mX, mY, mZ, mW;

	Quaternion& set( float x ,float y, float z, float w );
	Quaternion& copy( const Quaternion& q );
	Quaternion& setFromVector( const Vector3& v );
	Quaternion& setFromAngle( float angle, const Vector3& axis );

	float lenght();
	Quaternion& divideScalar( float scalar );
	Quaternion& normalize( );

};


#endif // QUATERNION_H
