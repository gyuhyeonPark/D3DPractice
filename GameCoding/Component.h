#pragma once
#include "Transform.h"

class GameObject;

enum class ComponentType
{
	Transform,
	MeshRenderer,
	Camera,
	Animator,
	// ...
	Script,
	End
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End) - 1
};

class Component
{
public:
	Component(ComponentType type);
	virtual ~Component();

	virtual void Awake() { }
	virtual void Start() { }
	virtual void Update() { }
	virtual void LateUpdate() { }
	virtual void FixedUpdate() { }

	shared_ptr<GameObject> GetGameObject() { return _gameObject.lock(); }
	shared_ptr<Transform> GetTransform();

	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }

protected:
	ComponentType _type;
	weak_ptr<GameObject> _gameObject;
};

