#ifndef COLOUR_H
#define COLOUR_H

#include "stdafx.h"
#include <cmath>

class Colour{
	public:
		Colour::Colour();
		Colour::Colour( float x, float y, float z );
		Colour::Colour( const Colour& vector );
		~Colour();
	
		Colour  operator *  ( float scalar );		// Scalar multiplication
		void	operator *= ( float scalar );
		Colour  operator /  ( float scalar );		// Scalar division
		void	operator /= ( float scalar );
		bool	operator == ( const Colour& rhs );	// Equality check
		void	operator += ( const Colour& rhs);
		Colour  operator +  ( const Colour& rhs );	// Addition
		Colour  operator *  ( const Colour& rhs );	// Colour multiplication
		void	operator *= ( const Colour& rhs );
		void	operator -= ( const Colour& rhs);
		Colour  operator -  ( const Colour& rhs );	// Subtraction

		static Colour add( const Colour& lhs, const Colour& rhs );
		static Colour subtract(const Colour& lhs, const Colour& rhs);

		Pixel createPixel();

		struct { float r, g, b; };

	private:
		void copy( const Colour& c );

};


#endif // COLOUR_H

