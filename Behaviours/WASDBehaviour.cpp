// TODO Fix WASDBehaviour

#include "../stdafx.h"

#include "WASDBehaviour.hpp"
#include "../GameObject.hpp"

WASDBehaviour::WASDBehaviour( GameObject * aParent ):	Behaviour( aParent ) {}
WASDBehaviour::~WASDBehaviour(){}

void WASDBehaviour::update( float step )
{
	/*

	glm::ivec2 windowCenter = glm::ivec2( window->getSize().x/2, window->getSize().y/2 );
	glm::ivec2 mousePosition = glm::ivec2( sf::Mouse::getPosition( *window ).x, sf::Mouse::getPosition( *window ).y );
	float turnHorizontal = 1.0f * (mousePosition.x - windowCenter.x) / windowCenter.x;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        parent->rotate( -50 * step * turnHorizontal, glm::vec3( 0.0f, 1.0f, 0.0f ) ); // rotates 45� per second
	}

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W )) {
		parent->translate( glm::vec3(0.0f, 0.0f, -step*30 ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A )) {
		parent->translate( glm::vec3( -step * 60, 0.0f, 0.0f ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S )) {
		parent->translate( glm::vec3(0.0f, 0.0f, step*30 ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D )) {
		parent->translate( glm::vec3( step * 60, 0.0f, 0.0f ) );
	}*/

	//std::cout << turnHorizontal << std::endl;
}
