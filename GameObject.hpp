#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm.hpp>
#include <vector>

class Vector3;
class Transform;
class Collider;
class Renderer;
class Mesh;
class Texture;
class Behaviour;
class ShaderProgram;
class Light;
class Ray;

class GameObject
{
	protected:
		std::string name;
		glm::mat4 transform;
		Behaviour * behaviour;
		Collider * collider;
		Mesh * mesh;
		Texture * mTexture;
        ShaderProgram * shader;
        Light * light;
		Ray * ray;
        float startTime;
        bool adding;
		std::vector<GameObject *> children;

	public:
		GameObject( std::string aName = "", glm::vec3 aPosition = glm::vec3( 0.0f, 0.0f, 0.0f ));
		//GameObject(std::string name = NULL, Vector3 position = Vector3( 0.0f, 0.0f, 0.0f ));

		virtual ~GameObject();

		void translate( glm::vec3 translation );
		void rotate( float angle, glm::vec3 axis );

		glm::mat4 getTransform( );
		const std::string getName( );
		Collider * getCollider( );
		glm::vec3 getLocation( );
		glm::vec3 getDirection( );
		bool hasCollider( );

		void setBehaviour( Behaviour * aBehaviour );
		void setShader( ShaderProgram * aShader );
		void setTexture( Texture * texture );

		Behaviour * getBehaviour( );
		void removeBehaviour( );
		void setCollider( Collider * aCollider );
		void removeCollider();
		void removeChild( GameObject * aChild );
		void setTransform( glm::mat4 aTransform );
		void setLocation( glm::vec3 aLocation );
		void setMesh( Mesh * aMesh );
		Mesh * getMesh();
		void makeQuad(int width, int height);

		void setLight(Light * aLight, ShaderProgram * aShader);
		Light * getLight();

		virtual void update( float step );
		virtual void onCollision(  GameObject * otherGameObject );
//		virtual void draw( Renderer * renderer, glm::mat4 parentTransform = glm::mat4(1) );
		virtual bool intersect( Ray& ray, float& distance );
//		void draw( );

		void add(GameObject * child);
};

#endif // GAMEOBJECT_H
