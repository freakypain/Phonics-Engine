#include <iostream>
#include <string>
#include "Light.hpp"

Light::Light(GameObject * aParent) : parent( aParent )
{
}

Light::~Light()
{
	//dtor
}

void Light::draw( Renderer * aRenderer, glm::mat4 parentTransform )
{
	//aRenderer->setLight( getLocation() );
	std::cout << "Wrong Light Renderer" << std::endl;
}
