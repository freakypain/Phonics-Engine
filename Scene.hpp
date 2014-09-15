#ifndef SCENE_H
#define SCENE_H

#include "GameObject.hpp"

class Camera;
class Light;
class Primitive;
class Ray;

class Scene : public GameObject
{
	public:
		Scene( std::string aName = "" );
		virtual ~Scene();

		void update( float step );
		void checkCollision();
		virtual void draw( Renderer * renderer );
		Primitive* getFirstPrimitive( Ray& ray, float& distanceToIntersect ) const;
		GameObject* getFirstGameObject(Ray& ray, float& distanceToIntersect);

	private:
		void setupScene();

		std::vector<Primitive*> mPrimitives;
		std::vector<GameObject*> mGameObjects;
};

#endif // WORLD_H
