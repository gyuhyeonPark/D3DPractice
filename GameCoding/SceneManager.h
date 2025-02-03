#pragma once

class Scene;
class Graphics;

class SceneManager
{
public:
	SceneManager(shared_ptr<Graphics> graphics, shared_ptr<Pipeline> pipeline);

	void Init();
	void Update();
	void LoadScene(wstring sceneName);

public:
	shared_ptr<Scene> GetActiveScene() { return _activeScene; }

public:
	shared_ptr<Scene> LoadTestScene();

private:
	shared_ptr<Graphics> _graphics;
	shared_ptr<Pipeline> _pipeline;
private:
	shared_ptr<Scene> _activeScene;
};

