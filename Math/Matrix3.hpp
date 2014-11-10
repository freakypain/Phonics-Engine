#ifndef MATRIX3_H
#define MATRIX3_H

// Internal
#include "../Math.hpp"
#include "Matrix4.hpp"

class Matrix3 : public Math
{
	public:
		union 
		{
			float data[4][4];
			float array[16];
		};

		Matrix3();
		~Matrix3();

		Matrix3& identity();
		Matrix3& transpose();
		Matrix3& getInverse(const Matrix4& matrix );


};

#endif
