#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Ray.hpp"

class Camera : public GameObject
{
	public:
		Camera( std::string aName = 0, glm::vec3 aPosition = glm::vec3( 0.0f, 3.0f, 5.0f ) );
		virtual ~Camera();
		void draw( Renderer * renderer, glm::mat4 parentTransform = glm::mat4(1) );
		bool intersect( Ray& ray, float& distance );

	private: //members
		glm::mat4 projection;
};


#endif // CAMERA_H
