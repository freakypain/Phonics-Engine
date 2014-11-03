#include <iostream>
#include <cassert>


#include "GameObject.hpp"
#include "Primitive.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Collider.hpp"

// Lights
#include "Light.hpp"
#include "Lights\PointLight.hpp"

// Primitives
#include "Primitive.hpp"
#include "Primitives\Sphere.hpp"
#include "Primitives\Plane.hpp"


Scene::Scene( std::string name ) : GameObject( name )
{

}

Scene::~Scene()
{
	//dtor
}

// Update scene
void Scene::update( float step )
{
	GameObject::update( step ); // Update Behaviour
	checkCollision(); // Check Collisions
}


// Return Number of primitives
Primitive* Scene::getPrimitive(int i)
{
	return mPrimitives[i];
}

//  Get nearest primitve 
// TODO Replace for Game Objects
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

void Scene::prepare(){
	// Loop through GameObjects
	for ( std::vector< GameObject * >::iterator i = children.begin(); i != children.end(); ++i ){	
		// Set lights
		if ( ( (GameObject *)* i)->getLight() ) { 
			mLights.push_back( ( ( GameObject *)* i)->getLight() ); 
		}

		// Set Primitives
		if (((GameObject *)* i)->getPrimitive()) {
			mPrimitives.push_back( ( ( GameObject *)* i)->getPrimitive() );
		}
	}
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
			Vector3 normal = primitive.getNormal( intersecPoint );
		//	Vector3 normal = 
			Vector3 toLight = ( (PointLight*)light )->getPosition() - intersecPoint;

			// Normalize Light
			float distToLight = toLight.length();
			toLight *= ( 1.0f / distToLight );

			// Determine primitive is in shadow
			bool inLight = true;
			Ray  shadowRay = Ray( intersecPoint + toLight * 0.0001f, toLight );

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
				float diffuseIntensity = Vector3::dot( toLight, normal ) * primitive.getMaterial()->mDiffuseFactor;

				// Is the primitive facing the light?
				if (diffuseIntensity > 0)				
					colourAtIntersect += ( primitive.getMaterial()->mDiffuse * light->getColour() ) * diffuseIntensity;
				

				// Calculate Specular
				Vector3 reflectedLight = toLight - normal * ( 2.0f * Vector3::dot( toLight, normal ) );
				float	reflectedLightAlongRay = Vector3::dot( rayDirection, reflectedLight );

				// Visible reflected Light
				if ( reflectedLightAlongRay > 0 )
				{
					float specularIntensity = powf( reflectedLightAlongRay, 25 ) * primitive.getMaterial()->mSpecular;
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
