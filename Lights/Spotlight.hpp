#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "../Light.hpp"


class Spotlight : public Light{
    public:
        Spotlight(GameObject * aParent);
        virtual ~Spotlight();
        void draw(Renderer * renderer, glm::mat4 parentTransform = glm::mat4(1));
};


#endif // SPOTLIGHT_H
