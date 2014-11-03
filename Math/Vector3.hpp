#ifndef VECTOR3_H
#define VECTOR3_H

#include "../Math.hpp"

class Vector3 : public Math {
	public:
		Vector3();
		Vector3( float x, float y, float z );
		Vector3( const Vector3& vector );
		~Vector3();

		// Operator Overloads
		Vector3  operator -  ( const Vector3& rhs );	// Subtraction
		void	 operator -= ( const Vector3& rhs );
		Vector3  operator +  ( const Vector3& rhs );	// Addition
		void	 operator += ( const Vector3& rhs );
		Vector3  operator *  ( float scalar );		// Scalar multiplication
		void	 operator *= ( float scalar );
		Vector3  operator /  ( float scalar );		// Scalar division
		void	 operator /= ( float scalar );
		bool	 operator == ( const Vector3& rhs );	// Equality check

		// Public Methods
		static float   dot( const Vector3& lhs, const Vector3& rhs );
		static Vector3 cross( const Vector3& lhs, const Vector3& rhs );
		static Vector3 normalize( const Vector3& vector );
		static Vector3 add( const Vector3& lhs, const Vector3& rhs );
		static Vector3 subtract( const Vector3& lhs, const Vector3& rhs );
		static Vector3 negate( const Vector3& vector );

		float length();
		float length() const;
		void  normalize();

		// XYZ components
		struct { float x, y, z; };

	private:
		void copy( const Vector3& v );
};

#endif // VECTOR3_H

