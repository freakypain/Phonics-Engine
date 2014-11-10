// Internal
#include "Quaternion.hpp"

// External
#include <cmath>
#include <limits>

Quaternion::Quaternion( float x, float y, float z, float w ) : mX(x), mY(y), mZ(z), mW(w)
{

}

Quaternion::~Quaternion()
{
	// Decon
}

Quaternion& Quaternion::set(float x, float y, float z, float w)
{
	mX = x,
	mY = y,
	mZ = z,
	mW = w;

	return *this;
}

Quaternion& Quaternion::copy(const Quaternion& v)
{
	mX = v.mX,
	mY = v.mY,
	mZ = v.mZ,
	mW = v.mW;

	return *this;
}

// http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
Quaternion& Quaternion::setFromVector(const Vector3& v)
{
	float c = 3.14159265358979323846f / 360.0f;
	mX = v.x * c;
	mY = v.y * c;
	mZ = v.z * c;

	float c1 = std::cos( mY );
	float s1 = std::sin( mY );
	float c3 = std::cos( mX );
	float s3 = std::sin( mX );
	float c2 = std::cos( -mZ );
	float s2 = std::sin( -mZ );
	
	float c1c2 = c1 * c2;
	float s1s2 = s1 * s2;

	mW = c1c2 * c3 - s1s2 * s3;
	mX = c1c2 * s3 + s1s2 * c3;
	mY = s1 * c2 * c3 + c1 * s2 * s3;
	mZ = c1 * s2 * c3 - s1 * c2 * s3;

	return *this;
}

Quaternion& Quaternion::setFromAngle(float angle, const Vector3& axis)
{
	float hAngle = angle / 2;
	float s = std::sin( hAngle );

	mW = axis.x * s;
	mY = axis.y * s;
	mZ = axis.z * s;
	mW = std::cos( hAngle );

	return *this;
}

float Quaternion::lenght()
{
	return std::sqrt(mX * mX + mY * mY + mZ * mZ + mW * mW);
}

Quaternion& Quaternion::divideScalar(float scalar)
{
	if (scalar > std::numeric_limits<float>::epsilon())
	{
		mX /= scalar;
		mY /= scalar;
		mZ /= scalar;
		mW /= scalar;
	}
	else{
		mX = 0;
		mY = 0;
		mZ = 0;
		mW = 0;
	}
	return *this;
}

Quaternion& Quaternion::normalize()
{
	return divideScalar(lenght());
}
