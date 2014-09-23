#include <iostream>
#include <cassert>


#include "GameObject.hpp"
#include "Primitive.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Collider.hpp"

#include "Lights\PointLight.hpp"


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

//Calculates  effect of light on a primitive & GameObject at a given point
GameObject* Scene::getFirstGameObject( Ray& ray, float& distanceToIntersect )
{
	GameObject* closestGameObject = 0;
	float distance = MAXDISTANCE;
	
	//for (std::vector<GameObject*>::iterator g = children.begin(); g != children.end(); ++g)
	for (std::vector<GameObject*>::iterator g = children.begin(); g != children.end(); ++g)
	{
		// TODO Fix value to be dynamic
		GameObject* currentGameObject = mGameObjects[0]; // Testing (Values needs to be G)

		if ( currentGameObject->intersect( ray, distance ) )
		{
			if ( distance < distanceToIntersect && distance > 0 )
			{
				distanceToIntersect = distance;
				closestGameObject = currentGameObject;
			}
		}		
	}

	return closestGameObject;
}

Colour Scene::calcuatePrimiateLightingAtPoint( Primitive& primitive, Vector3& intersecPoint, Vector3 rayDirection )
{
	Colour colourAtIntersect;

	// Calculate lighting for each point light
	for (UINT l = 0; l < mLights.size(); l++)
	{
		Light* light = mLights[l];

		if (light->getType() == LIGHT_POINT)
		{
			Vector3 normal = primitive.getNormal(intersecPoint);
			Vector3 toLight = ((PointLight*)light)->getPosition() - intersecPoint;

			// Normalize Light
			float distToLight = toLight.length();
			toLight *= ( 1.0f / distToLight );

			// Determine primitive is in shadow
			bool inLight = true;
			Ray  shadowRay = Ray(intersecPoint + toLight * 0.0001f, toLight);

			for (UINT p = 0; p < mPrimitives.size(); p++)
			{
				Primitive* primitiveToTest = mPrimitives[p];

				// Does the ray intersect a primitive before it hits the light?
				if (primitiveToTest->getShadow())
				{
					if (primitiveToTest->intersect(shadowRay, distToLight))
					{
						inLight = false;
						break;
					}
				}
			}

			if ( inLight == true )
			{
				// Calculate diffuse component
				float diffuseIntensity = Vector3::dot(toLight, normal) * primitive.getMaterial()->diffuseFactor;

				// Is the primitive facing the light?
				if (diffuseIntensity > 0)
				{
					colourAtIntersect += (primitive.getMaterial()->diffuse * light->getColour()) * diffuseIntensity;
				}

				// Calculate Specular
				Vector3 reflectedLight = toLight - normal * (2.0f * Vector3::dot(toLight, normal));
				float	reflectedLightAlongRay = Vector3::dot(rayDirection, reflectedLight);

				// Visible reflected Light
				if ( reflectedLightAlongRay > 0 )
				{
					float specularIntensity = powf(reflectedLightAlongRay, 25) * primitive.getMaterial()->specular;
					colourAtIntersect += light->getColour() * specularIntensity;
				}
			}
		}
	}

	return colourAtIntersect;
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