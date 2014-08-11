#include "Collider.hpp"
#include "GameObject.hpp"

Collider::Collider(GameObject * aParent) : parent( aParent ){

}

Collider::~Collider()
{

}

bool Collider::collides(Collider * otherCollider){
    return false;
}

bool Collider::collides(SphereCollider * otherCollider){
    return false;
}
