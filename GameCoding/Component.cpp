#include "pch.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

Component::Component()
{
}

Component::Component(ComponentType type)
    : _type(type)
{

}

Component::~Component()
{

}

shared_ptr<Transform> Component::GetTransform()
{
    return _gameObject.lock()->GetTransform();
}
