#ifndef COLLIDER_H
#define COLLIDER_H

class GameObject;
class SphereCollider;

class Collider
{
    protected:
        GameObject *parent;

    public:
        Collider(GameObject *aParent);
        virtual ~Collider();
        virtual bool collides(Collider* otherCollider);
        virtual bool collides(SphereCollider* otherCollider);

};

#endif // COLLIDER_H
