#include <iostream>
#include <string>
#include <gtc\matrix_transform.hpp>
#include <glm.hpp>

#include "Camera.hpp"
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Ray.hpp"



Camera::Camera( std::string name, glm::vec3 position ) : GameObject( name, position )
{
	glm::vec3 eye = position;
	glm::vec3 at( position.x, 0, position.z + 0.01 );
	glm::vec3 up ( 0.0f, -1.0f, 0.0f );
	transform = glm::inverse( glm::lookAt( eye, at, up ) );
	projection = glm::perspective(  60.0f, 4.0f/3.0f, 0.1f, 100.0f  );
}

Camera::~Camera()
{
	//dtor
}


// TODO Fix Intersection of Gameobjects
bool Camera::intersect( Ray& ray, float& distance )
{	

	std::cout << distance << std::endl;

	bool intersect = false;

	float dotPlane = Vector3::dot(mNormal, ray.getDirection());

	if (dotPlane < 0)
	{
		float distToIntersect = -(Vector3::dot(ray.getOrigin(), mNormal) + mDistance) / dotPlane;
		if (distToIntersect < MAXDISTANCE)
		{
			distance = distToIntersect;
			intersect = true;
		}
	}

	return intersect;
}
