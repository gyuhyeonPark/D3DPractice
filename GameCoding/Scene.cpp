#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::Awake()
{
	for (const shared_ptr<GameObject>& obj : _gameObjects)
	{
		obj->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject>& obj : _gameObjects)
	{
		obj->Start();
	}
}

void Scene::Update()
{
	for (const shared_ptr<GameObject>& obj : _gameObjects)
	{
		obj->Update();
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject>& obj : _gameObjects)
	{
		obj->LateUpdate();
	}
}

void Scene::FixedUpdate()
{
	for (const shared_ptr<GameObject>& obj : _gameObjects)
	{
		obj->FixedUpdate();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> obj)
{
	_gameObjects.push_back(obj);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> obj)
{
	auto findIt = std::find(_gameObjects.begin(), _gameObjects.end(), obj);
	if (findIt != _gameObjects.end())
		_gameObjects.erase(findIt);
}

const vector<shared_ptr<GameObject>> Scene::GetGameObjects()
{
	return _gameObjects;
}
