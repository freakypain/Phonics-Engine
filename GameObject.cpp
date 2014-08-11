#include <cassert>
#include <iostream>

#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Behaviour.hpp"
#include "Collider.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Time.hpp"
#include "ShaderProgram.hpp"
#include "Light.hpp"

GameObject::GameObject( std::string aName, glm::vec3 aPosition )
:	name( aName ), transform( glm::translate( aPosition ) ), behaviour( NULL ), collider(NULL), mesh( NULL ), tex0( NULL ), tex1( NULL ), tex2( NULL ), tex3( NULL ), shader(NULL), light(NULL), totalSprite(0), startTime(0.0f), currentSprite(0) // initialisation list
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
   transform = glm::translate(transform[3][aLocation.x], transform[3][aLocation.y], transform[3][aLocation.z] );
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

void GameObject::setBehaviour( Behaviour * aBehaviour )
{
	assert( aBehaviour != NULL );
	behaviour = aBehaviour;
}

void GameObject::setShader(ShaderProgram * aShader)
{
    assert(aShader != NULL);
    shader = aShader;
}

bool GameObject::hasCollider()
{
    if(collider != NULL) return true;

    return false;
}

Collider * GameObject::getCollider(){
    return collider;
}

void GameObject::setCollider(Collider *aCollider)
{
    assert( aCollider != NULL );
	collider = aCollider;
}

void GameObject::removeCollider(){
    collider = NULL;
}

Behaviour * GameObject::getBehaviour(){
    return behaviour;
}

void GameObject::removeBehaviour(){
    behaviour = NULL;
}

Mesh * GameObject::getMesh(){
    return mesh;
}

void GameObject::setMesh( Mesh * aMesh )
{
	assert( aMesh != NULL );
	mesh = aMesh;
}

void GameObject::setTexture0( Texture * aTex )
{
	assert( aTex != NULL );
	assert( aTex->getId() > 0 );
	tex0 = aTex;
}

void GameObject::setLight(Light * aLight, ShaderProgram * aShader)
{
    assert(aLight != NULL);
    assert(aShader != NULL);
    light = aLight;
    shader = aShader;
}

Light * GameObject::getLight()
{
    return light;
}

void GameObject::update( float step )
{
	if ( behaviour ) { // note no assert on behaviour, it is ok when there is no behaviour
		behaviour->update( step );
	}

	float time = Time::now();
	if (time - startTime >= 0.05f ) {
		startTime = time;
        if(currentSprite >= 1){
            (currentSprite >= totalSprite) ? currentSprite = 1 : currentSprite ++;
        }
	}
	for ( size_t i = 0; i < children.size(); ++i ) {
		children[i]->update( step );
	}
}

void GameObject::onCollision(  GameObject * otherGameObject )
{
	if ( behaviour ) {
		behaviour->onCollision( otherGameObject );
	}
}


void GameObject::draw( Renderer * aRenderer, glm::mat4 parentTransform )
{
	assert( aRenderer != NULL );

    if( shader ){
        aRenderer->setShader( shader );
    }

    if( light ){
        light->draw(aRenderer);
    }

	if( mesh ) { // if there is something to draw
		aRenderer->setModel( parentTransform * transform ); // combine parents transfor with own

		if( shader ){
            aRenderer->setShader(shader);
		}

		if( tex0 ) { //is has a colormap
			aRenderer->setTexture0( tex0 );
		}

		mesh->draw( aRenderer );
	}

	// draw children
	for( std::vector< GameObject * >::iterator i = children.begin(); i != children.end(); ++i ) {
		((GameObject * )*i)->draw( aRenderer, parentTransform * transform );
	}
}

glm::mat4 GameObject::getTransform(){
    return transform;
}

void GameObject::set2DAnimation(int total)
{
    currentSprite = 2;
    totalSprite = total;
}

void GameObject::add( GameObject * child )
{
	assert( child != NULL );
	children.push_back( child );
}

void GameObject::removeChild( GameObject * child)
{
    assert(child!= NULL);
    try{
        for( std::vector< GameObject * >::iterator it = children.begin(); it != children.end(); it++ )
        {
            if( *it == child )
            {
                ((GameObject *)*it)->removeCollider();
                ((GameObject *)*it)->removeBehaviour();
                ((GameObject *)*it)->currentSprite = 0;
                ((GameObject *)*it)->setMesh(NULL);
            }
        }
    }catch( std::string e ){
                std::cout<<e<<std::endl;
            }
}
// private functions

