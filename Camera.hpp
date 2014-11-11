#ifndef CAMERA_H
#define CAMERA_H


#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Ray.hpp"
#include "Math\Vector3.hpp"
#include "Math\Matrix4.hpp"


class Camera : public GameObject
{
	public:
		Camera( std::string name = 0, Vector3 position = Vector3( 0.0f, 3.0f, 5.0f ) );
		virtual ~Camera();
		bool intersect( Ray& ray, float& distance );

	private: //members
		Matrix4 mProjection;
		Vector3 mNormal;
		float mDistance;
};


#endif // CAMERA_H
