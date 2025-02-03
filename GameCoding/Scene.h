#pragma once

class GameObject;

class Scene
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

public:
	void AddGameObject(shared_ptr<GameObject> obj);
	void RemoveGameObject(shared_ptr<GameObject> obj);
	
	const vector<shared_ptr<GameObject>> GetGameObjects();

private:
	vector<shared_ptr<GameObject>> _gameObjects;
};

