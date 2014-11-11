#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// External
#include <vector>
#include "Primitive.hpp"

// Internal
#include "Math\Matrix4.hpp"
#include "Math\Vector3.hpp"


class Collider;
class Renderer;
class Behaviour;
class Light;
class Ray;
class Light;

class GameObject
{
	public:
		GameObject( std::string mName = "", Vector3 position = Vector3( 0.0f, 0.0f, 0.0f ));
		//GameObject(std::string name = NULL, Vector3 position = Vector3( 0.0f, 0.0f, 0.0f ));

		virtual ~GameObject();

		void translate( Vector3 translation );
		void rotate( float angle, Vector3 axis );

		Matrix4 getTransform( );
		const std::string getName( );
		Collider * getCollider( );
		Vector3 getLocation( );
		Vector3 getDirection( );
		bool hasCollider( );

		void setBehaviour( Behaviour * aBehaviour );

		Behaviour * getBehaviour( );
		void removeBehaviour( );
		void setCollider( Collider * aCollider );
		void removeCollider();
		void removeChild( GameObject * aChild );
		void setTransform( Matrix4 aTransform );
		void setLocation( Vector3 aLocation );
		void setPrimitive( Primitive * primitive );
		Primitive * getPrimitive();
		std::vector<GameObject*> getGameObjects();
		void makeQuad(int width, int height);

		void setLight(Light * light);
		Light * getLight();

		virtual void update( float step );
		virtual void onCollision(  GameObject * otherGameObject );
//		virtual void draw( Renderer * renderer, glm::mat4 parentTransform = glm::mat4(1) );
		virtual bool intersect( Ray& ray, float& distance );
//		void draw( );

		void add( GameObject * child );

	protected:
		std::string mName;
		//glm::mat4 transform;
		Matrix4 mTransform;
		Behaviour * behaviour;
		Collider * collider;
		Light * mLight;
		Ray * ray;
		Primitive * mPrimitive;
		float startTime;
		bool adding;
		std::vector<GameObject*> children;

};

#endif // GAMEOBJECT_H
