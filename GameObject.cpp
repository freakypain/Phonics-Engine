// Libs
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Behaviour.hpp"
#include "Collider.hpp"
#include "Time.hpp"
#include "Light.hpp"
#include "Ray.hpp"

// Temp
#include "Camera.hpp"

// C++
#include <vector>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>




GameObject::GameObject(std::string aName, glm::vec3 aPosition) : 
																name(aName), transform(glm::translate(glm::mat4(1.0f), aPosition)), 
																behaviour(nullptr), collider(nullptr), mesh(nullptr),
																mLight(nullptr), ray(nullptr), mPrimitive(nullptr), children()
{

}

GameObject::~GameObject()
{
	//dtor
}


void GameObject::translate(glm::vec3 translation)
{
	
	transform = glm::translate( transform, translation );

}


void GameObject::setTransform(glm::mat4 aTransform)
{
    transform = aTransform;
}


void GameObject::setLocation(glm::vec3 aLocation)
{
	transform = glm::translate(transform, glm::vec3(transform[3][aLocation.x], transform[3][aLocation.y], transform[3][aLocation.z]));
}


glm::vec3 GameObject::getDirection()
{
    return glm::vec3(transform[2]); // z axis return
}


void GameObject::rotate( float angle, glm::vec3 axis )
{
	transform = glm::rotate( transform, angle, axis);
}


const std::string GameObject::getName()
{
	return name;
}

glm::vec3 GameObject::getLocation()
{
	return glm::vec3( transform[3][0], transform[3][1], transform[3][2] );
}

// Return GameObjects
std::vector<GameObject*> GameObject::getGameObjects()
{
	return children;
}

void GameObject::setBehaviour( Behaviour * aBehaviour )
{
	assert( aBehaviour != 0 );
	behaviour = aBehaviour;
}


bool GameObject::hasCollider()
{
    if(collider != 0)
		return true;

    return false;
}


Collider * GameObject::getCollider(){
    return collider;
}

void GameObject::setCollider(Collider *aCollider)
{
    assert( aCollider != 0 );
	collider = aCollider;
}


void GameObject::removeCollider(){
    collider = 0;
}

Behaviour * GameObject::getBehaviour(){
    return behaviour;
}


void GameObject::removeBehaviour(){
    behaviour = 0;
}


Mesh * GameObject::getMesh(){
    return mesh;
}

void GameObject::setMesh( Mesh * aMesh )
{
	assert( aMesh != 0 );
	mesh = aMesh;
}

void GameObject::setPrimitive(Primitive * primitive)
{
	assert( primitive != 0 );
	mPrimitive = primitive;
}


void GameObject::setLight(Light * light)
{
	assert(light != 0);
	mLight = light;
}


Light * GameObject::getLight()
{
	return mLight;
}

Primitive * GameObject::getPrimitive()
{
	return mPrimitive;
}


void GameObject::update( float step )
{
	if ( behaviour ) { // note no assert on behaviour, it is ok when there is no behaviour
		behaviour->update( step );
	}

	float time = Time::now();

	if (time - startTime >= 0.05f ) {
		startTime = time;
	}
}


void GameObject::onCollision(  GameObject * otherGameObject )
{
	if ( behaviour ) {
		behaviour->onCollision( otherGameObject );
	}
}


// TODO Fix intersect
bool GameObject::intersect( Ray& ray, float& distance )
{
	return false;
}


glm::mat4 GameObject::getTransform(){
    return transform;
}


void GameObject::add( GameObject * child )
{
	assert( child != 0 );
	children.push_back( child );
}


void GameObject::removeChild( GameObject * child )
{
    assert(child!= 0);
    try{
        for( std::vector< GameObject * >::iterator it = children.begin(); it != children.end(); it++ )
        {
            if( *it == child )
            {
                ((GameObject *)*it)->removeCollider();
                ((GameObject *)*it)->removeBehaviour();
                ((GameObject *)*it)->setMesh(0);
            }
        }
    }
	catch( std::string e ){
		throw;
    }
}