#include <Windows.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include <glm.hpp>

#include "SphereCollider.hpp"
#include "../Behaviour.hpp"
#include "../GameObject.hpp"






SphereCollider::SphereCollider( GameObject * aParent, float aRadius ) :	Collider( aParent ), radius( aRadius )
{
	//ctor
	//std::cout << parent->getName() << std::endl;
	// TODO Fix get parents name
	std::cout << "Parent Name: (Needs to be fixed) " << std::endl;
}

SphereCollider::~SphereCollider()
{
	//dtor
}

bool SphereCollider::collides( Collider * otherCollider )
{
	return otherCollider->collides( this );
}



void drawSphere(){

}


bool SphereCollider::collides( SphereCollider * otherCollider )
{
    glm::vec3 position = parent->getLocation();
    glm::vec3 otherPosition = otherCollider->parent->getLocation();

    float distance = glm::distance(position, otherPosition);

    if(distance < radius + otherCollider->radius){
            if(parent->getBehaviour() != 0){
                parent->getBehaviour()->onCollision(otherCollider->parent);
                return true;
            }
    }
    else if(parent->getBehaviour() != 0){
        parent->getBehaviour()->onCollisionExit(otherCollider->parent);
    }
    return false;
}
