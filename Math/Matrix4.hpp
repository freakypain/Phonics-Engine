#ifndef MATRIX_H
#define MATRIX_H

// Internal
#include "../Math.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"

class Matrix4 : public Math
{
public:

	union
	{
		float data[4][4];
		float array[16];
	};
	
	Matrix4();
	Matrix4( const Matrix4& mat );
	~Matrix4();

	Matrix4& operator=	( const Matrix4 &matrix) ;
	Matrix4 operator*	( const Matrix4 &matrix ) const;
	Matrix4 operator*	( const float scalar ) const;	
	Vector3 operator*	( const Vector3 vec3 ) const;
	void operator*=		( const float scalar );
	void operator*=		( const Matrix4 &matrix );


	Matrix4& set( float n11, float n12, float n13, float n14,
					float n21, float n22, float n23, float n24,
					float n31, float n32, float n33, float n34,
					float n41, float n42, float n43, float n44 );

	Matrix4& identity( );
	Matrix4& zero( );
	Matrix4& copy( const Matrix4 &matrix );
	Matrix4& transpose( );
	Matrix4& lookAt( const Vector3& eye, const Vector3& target, const Vector3& up );
	Matrix4& lookAt2( const Vector3& eye, const Vector3& target, const Vector3& up );
	Matrix4& setPerspective( float fov, float ratio, float near, float far );
	Matrix4& setOrthogonal( float left, float right, float top, float bottom, float near, float far );
	Matrix4& setRotationMatrix( float angle, const Vector3 &xyz );
	Matrix4& setRotationMatrix( const Quaternion& q );
	Matrix4& setPosition( const Vector3& xyz );
	Matrix4& translate( const Vector3 &xyz );
	Matrix4& rotate( float angle, const Vector3 &xyz );
	Matrix4& scale( const Vector3& xyz );

	float determinant() const;
	Matrix4 inverse( ) const;
	
	Vector3& rotateAxis( Vector3& axis );	
};
#endif // MATRIX_H

