#ifndef LIGHT_H
#define LIGHT_H


#include "GameObject.hpp"
class Renderer;
class Spotlight;

class Light
{
    protected:
        GameObject * parent;

	public:
		Light( GameObject * aParent );
		virtual ~Light();
		virtual void draw( Renderer * aRenderer, glm::mat4 parentTransform = glm::mat4(1) );
};

#endif // LIGHT_H
