#ifndef SCENE_H
#define SCENE_H

#include "GameObject.hpp"

class Camera;
class Light;

class Scene : public GameObject
{
	public:
		Scene(std::string aName = 0);
		virtual ~Scene();

		void update( float step );
		void checkCollision();
		virtual void draw( Renderer * renderer );

};

#endif // WORLD_H
