#include "Primitive.hpp"
#include "Vector3.hpp"
#include "Colour.hpp"


Primitive::Primitive(bool castShadow = true) : mCastShadows(castShadow)
{

}

Primitive::~Primitive()
{

}

// TODO Fix colour the returning of the colour and material
//Colour Primitive::getColour( Vector3&  )