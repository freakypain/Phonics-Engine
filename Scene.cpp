#include <cassert>
#include "Scene.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Collider.hpp"

Scene::Scene(std::string aName) : GameObject(aName)
{
	//ctor
}

Scene::~Scene()
{
	//dtor
}

void Scene::update(float step)
{
	//camera->update( step );
	GameObject::update( step );
	checkCollision(); // Check Collisions
}

void Scene::draw(Renderer * renderer)
{
	assert( renderer != NULL );
	GameObject::draw( renderer ); // draw children Engine Objects
}

void Scene::checkCollision(){
    for ( std::vector< GameObject * >::iterator i = children.begin(); i != children.end(); ++i ){
        if(((GameObject * ) * i)->hasCollider()){
            for ( std::vector< GameObject * >::iterator j = i + 1; j != children.end(); ++j ){
                if(((GameObject *) * j)->hasCollider()){
                    ((GameObject *) *i)->getCollider()->collides(((GameObject *) *j)->getCollider());
                }
            }
        }
    }
}
