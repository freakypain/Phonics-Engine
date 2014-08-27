#include "Colour.hpp"

Colour::Colour( void ) : r( 0 ), g( 0 ), b( 0 ) {};
Colour::Colour( float r, float g, float b ) : r( r ), g( g ), b( b ) {};

Colour::Colour( const Colour& v )
{
	copy( v );
}

Colour::~Colour(void)
{

}

Colour Colour::	operator -  (const Colour& rhs )
{
	return Colour::subtract( *this, rhs );
}

void Colour:: operator -= ( const Colour& rhs )
{
	r += rhs.r;
	g += rhs.g;
	b += rhs.b;
}

Colour Colour::	operator + ( const Colour& rhs )
{
	return Colour::add( *this, rhs );
}

void Colour:: operator += ( const Colour& rhs )
{
	r += rhs.r;
	g += rhs.g;
	b += rhs.b;
}

Colour Colour:: operator * ( const Colour& rhs )
{
	return Colour( r * rhs.r, g * rhs.g, b * rhs.b) ;
}

void Colour:: operator *= ( const Colour& rhs )
{
	r *= rhs.r;
	g *= rhs.g;
	b *= rhs.b;
}

Colour Colour::	operator * ( float scalar )
{
	return Colour( r * scalar, g * scalar, b * scalar );
}

void Colour:: operator *= ( float scalar )
{
	r *= scalar;
	g *= scalar;
	b *= scalar;
}

Colour Colour::	operator /	( float scalar )
{
	float oneOverScalar = 1.0f / scalar;
	return Colour( r * oneOverScalar, g * oneOverScalar, b * oneOverScalar );
}

void Colour:: operator /= ( float scalar )
{
	float oneOverScalar = 1.0f / scalar;
	r *= oneOverScalar;
	g *= oneOverScalar;
	b *= oneOverScalar;
}

bool Colour:: operator == ( const Colour& rhs )
{
	return (( r == rhs.r ) && ( g == rhs.g ) && ( b == rhs.b ));
}

Colour Colour::add( const Colour& lhs, const Colour& rhs )
{
	return Colour(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
}

Colour Colour::subtract( const Colour& lhs, const Colour& rhs )
{
	return Colour(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
}

Pixel Colour::createPixel()
{
	int red = (int)(r * 256);
	int green = (int)(g * 256);
	int blue = (int)(b * 256);

	if (red > 255)		red = 255;
	if (green > 255)	green = 255;
	if (blue > 255)		blue = 255;

	return (red << 16) | (green << 8) | blue;
}

void Colour::copy( const Colour& c )
{
	r = c.r;
	g = c.g;
	b = c.b;
}