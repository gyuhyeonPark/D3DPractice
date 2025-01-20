#include "pch.h"
#include "Component.h"

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
