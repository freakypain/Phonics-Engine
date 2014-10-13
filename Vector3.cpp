#include "Vector3.hpp"
#include <cmath>


Vector3::Vector3( void ) : x( 0 ), y( 0 ), z( 0 ) {};

Vector3::Vector3( float x, float y, float z )	: x( x ), y( y ), z( z ) {};

Vector3::Vector3( const Vector3& v )
{
	copy(v);
}

Vector3::~Vector3( void )
{

}

Vector3 Vector3:: operator - ( const Vector3& rhs )
{
	return Vector3::subtract( *this, rhs );
}

void Vector3:: operator -= ( const Vector3& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

Vector3 Vector3:: operator + ( const Vector3& rhs )
{
	return Vector3::add( *this, rhs );
}

void Vector3:: operator +=	( const Vector3& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

Vector3 Vector3:: operator * ( float scalar )
{
	return Vector3( x * scalar, y * scalar, z * scalar );
}

void Vector3:: operator *=	( float scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

Vector3 Vector3:: operator / ( float scalar )
{
	float oneOverScalar = 1.0f / scalar;
	return Vector3( x * oneOverScalar, y * oneOverScalar, z * oneOverScalar );
}

void Vector3:: operator /=	(float scalar)
{
	float oneOverScalar = 1.0f / scalar;
	x *= oneOverScalar;
	y *= oneOverScalar;
	z *= oneOverScalar;
}

bool Vector3::		operator ==	(const Vector3& rhs)
{
	return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
}

// Calculates the Vector3.Vector3.Distanceot/scalar product of two vectors.
float Vector3::dot(const Vector3& lhs, const Vector3& rhs)
{
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

// Calculates the cross product of two vectors. Returns a vector perpendicular to both.
Vector3 Vector3::cross(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 crossProduct;

	crossProduct.x = (lhs.y * rhs.z) - (lhs.z * rhs.y);
	crossProduct.y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
	crossProduct.z = (lhs.x * rhs.y) - (lhs.y * rhs.x);

	return crossProduct;
}

// Adds two vectors together and returns the result.
Vector3 Vector3::add(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

// Subtracts one vector from another and returns the result.
Vector3 Vector3::subtract(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

// Normalizes the vector (makes its length/magnitude = 1).
void Vector3::normalize()
{

	if (length() != 0)
	{
		float oneOverLength = 1.0f / length();
		x *= oneOverLength;
		y *= oneOverLength;
		z *= oneOverLength;
	}
}

// Normalizes a vector (makes its length/magnitude = 1) and returns a new vector.
Vector3 Vector3::normalize(const Vector3& vector)
{
	if (vector.length() != 0)
	{
		Vector3 normalized;

		float oneOverLength = 1.0f / vector.length();
		normalized.x = vector.x * oneOverLength;
		normalized.y = vector.y * oneOverLength;
		normalized.z = vector.z * oneOverLength;

		return normalized;
	}

	return vector;
}

// Returns the negated version of a vector
Vector3 Vector3::negate(const Vector3& vector)
{
	return Vector3(-vector.x, -vector.y, -vector.z);

}

// Calculates the length/magnitude of a vector
float Vector3::length()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

float Vector3::length() const
{
	return sqrt((x * x) + (y * y) + (z * z));
}

// Copies the contents of one vertex to this one.
void Vector3::copy(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}