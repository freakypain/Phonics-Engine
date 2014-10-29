#ifndef SCENE_H
#define SCENE_H

// C++
#include <vector>

// Project
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Colour.hpp"
#include "Primitive.hpp"


class Scene : public GameObject
{
	public:
		Scene( std::string aName = "" );
		virtual ~Scene();

		void update( float step );
		void checkCollision();
		void prepare();

		Primitive* getFirstPrimitive( Ray& ray, float& distanceToIntersect ) const;
		Colour calcuatePrimiateLightingAtPoint( Primitive& primitive, Vector3& intersecPoint, Vector3 rayDirection );
	

		int getPrimitiveCount();
		Primitive* getPrimitive(int i);

	private:
		std::vector<Primitive*> mPrimitives;
		std::vector<Light*> mLights; 
};

#endif // WORLD_H
