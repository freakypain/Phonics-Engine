#include <iostream>
#include <cassert>


#include "GameObject.hpp"
#include "Primitive.hpp"
#include "Ray.hpp"
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

// Update scene
void Scene::update( float step )
{
	//camera->update( step );
	GameObject::update( step );
	checkCollision(); // Check Collisions
}

// Draw Scene
void Scene::draw( Renderer * renderer )
{
	assert( renderer != 0 );
	GameObject::draw( renderer ); // draw children Engine Objects
}

//  Get nearest primitve 
// TODO Replace for Game Object
Primitive* Scene::getFirstPrimitive(Ray& ray, float& distanceToIntersect) const
{
	Primitive* nearestPrimitive = 0;
	float distance = MAXDISTANCE;

	// Find nearest primitive
	for ( unsigned int p = 0; p < mPrimitives.size(); p++ )
	{
		Primitive* currentPrimitive = mPrimitives[p];

		// Ray intersect primitive
		if ( currentPrimitive->intersect( ray, distance ) )
		{
			// Intersection out of range
			if ( distance < distanceToIntersect && distance > 0 )
			{
				distanceToIntersect = distance;
				nearestPrimitive = currentPrimitive;
			}
		}
	}

	return nearestPrimitive;
}


GameObject* Scene::getFirstGameObject( Ray& ray, float& distanceToIntersect )
{
	GameObject* closestGameObject = 0;
	float distance = MAXDISTANCE;

	//for (std::vector<GameObject*>::iterator g = children.begin(); g != children.end(); ++g)
	for (std::vector<GameObject*>::iterator g = children.begin(); g != children.end(); ++g)
	{
		GameObject* currentGameObject = mGameObjects[0]; // Testing (Values needs to be G)

		if ( currentGameObject->intersect( ray, distance ) )
		{
			if ( distance < distanceToIntersect && distance > 0 )
			{
				distanceToIntersect = distance;
				closestGameObject = currentGameObject;
			}

		}

		return closestGameObject;
	}
}

// Look for colliders
void Scene::checkCollision(){
    for ( std::vector< GameObject * >::iterator i = children.begin(); i != children.end(); ++i ){
        if(((GameObject * ) * i)->hasCollider()){
            for ( std::vector< GameObject * >::iterator j = i + 1; j != children.end(); ++j ){
                if(((GameObject *) * j)->hasCollider()){
                    ((GameObject *) *i)->getCollider()->collides( ( (GameObject *) *j)->getCollider() );
                }
            }
        }
    }
}