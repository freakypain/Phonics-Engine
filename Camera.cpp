#include <iostream>
#include <string>

#include "Math\Vector3.hpp"
#include "Math\Matrix4.hpp"

#include "Camera.hpp"
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Ray.hpp"



Camera::Camera( std::string name, Vector3 position ) : GameObject( name, position )
{
	Vector3 eye = position;
	Vector3 at(position.x, 0, position.z + 0.01);
	Vector3 up(0.0f, -1.0f, 0.0f);

	// Test calculation
	Matrix4 matrix;
	mTransform = matrix.lookAt(eye, at, up);
	mTransform = matrix.inverse();
	mProjection = matrix.setPerspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		
	
	//transform = glm::inverse( glm::lookAt( eye, at, up ) );
	//projection = glm::perspective(  60.0f, 4.0f/3.0f, 0.1f, 100.0f  );
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
