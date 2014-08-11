#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include "glm.hpp"

class Transform;
class Collider;
class Renderer;
class Mesh;
class Texture;
class Behaviour;
class ShaderProgram;
class Light;

class GameObject
{
	protected:
		std::string name;
		glm::mat4 transform;
		Behaviour * behaviour;
		Collider * collider;
		Mesh * mesh;
		Texture * tex0;
        ShaderProgram * shader;
        Light * light;
        int totalSprite;
        float startTime;
        bool adding;
		std::vector<GameObject *> children;

	public:
		GameObject( std::string aName = NULL, glm::vec3 aPosition = glm::vec3( 0.0f, 0.0f, 0.0f ) );

		virtual ~GameObject();

		void translate( glm::vec3 translation );
		void rotate( float angle, glm::vec3 axis );

		glm::mat4 getTransform();


		const std::string getName();
		Collider * getCollider();
		glm::vec3 getLocation();
		glm::vec3 getDirection();
		bool hasCollider();

		void setBehaviour( Behaviour * aBehaviour );
		void setShader( ShaderProgram * aShader );
		Behaviour * getBehaviour();
		void removeBehaviour();
		void setCollider(Collider * aCollider);
		void removeCollider();
		void setTransform(glm::mat4 aTransform);
		void setLocation(glm::vec3 aLocation);
		void setMesh( Mesh * aMesh );
		Mesh * getMesh();
		void makeQuad(int width, int height);
		void setTexture0( Texture * aTex );

		void setLight(Light * aLight, ShaderProgram * aShader);
		Light * getLight();

		virtual void update( float step );
		virtual void onCollision(  GameObject * otherGameObject );
		virtual void draw( Renderer * renderer, glm::mat4 parentTransform = glm::mat4(1) );

	protected:

};

#endif // GAMEOBJECT_H
