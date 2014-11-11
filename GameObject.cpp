// Interanl
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Behaviour.hpp"
#include "Collider.hpp"
#include "Time.hpp"
#include "Light.hpp"
#include "Ray.hpp"

// (Internal) Math Libs
#include "Math\Vector3.hpp"
#include "Math\Matrix4.hpp" 

// External
#include <vector>
#include <cassert>



GameObject::GameObject(std::string name, Vector3 position) : 
															mName(name), mTransform(), //transform(glm::translate(glm::mat4(1.0f),  //Vector3( position.x, position.y, position.z),
															/*glm::vec3(position.x,position.y,position.z))),*/ behaviour(nullptr), collider(nullptr), 
															mLight(nullptr), ray(nullptr), mPrimitive(nullptr), children()
{

}

GameObject::~GameObject()
{
	//dtor
}


void GameObject::translate(Vector3 translation)
{
	//mTransform = Matrix4::translate()
	//transform = glm::translate( transform, translation );

}


void GameObject::setTransform(Matrix4 aTransform)
{
    mTransform = aTransform;
}

// TODO need to have a look at this
void GameObject::setLocation(Vector3 aLocation)
{
	Matrix4 matrix;
	mTransform = matrix.translate(Vector3(aLocation.x, aLocation.y, aLocation.z));
	
	//mTransform = glm::translate(Vector3(mTransform[3][aLocation.x], mTransform[3][aLocation.y], mTransform[3][aLocation.z]));
}


Vector3 GameObject::getDirection()
{
	return Vector3(mTransform.data[0][0], mTransform.data[1][0], mTransform.data[2][0]); // z axis return
}

// TODO: Need to have a look at this! 
void GameObject::rotate( float angle, Vector3 axis )
{
	Matrix4 matrix;
	matrix.identity(); // Lets give this one a try

	const Vector3 transform = Vector3(mTransform.data[0][0], mTransform.data[1][0], mTransform.data[2][0]);
	mTransform = matrix.rotate(angle, transform);

	//mTransform = Matrix4::rotate(mTransform, angle, axis);
}


const std::string GameObject::getName()
{
	return mName;
}

//TODO Need to have a look at this
Vector3 GameObject::getLocation()
{
	return Vector3( mTransform.data[0][0], mTransform.data[1][0], mTransform.data[2][0]);
	//return Vector3(mTransform[3][0], mTransform[3][1], mTransform[3][2]);
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


Matrix4 GameObject::getTransform(){
	return mTransform;
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
            }
        }
    }
	catch( std::string e ){
		throw;
    }
}