#pragma once

class Graphics;
class GameObject;
class SceneManager;
class InputManager;
class TimeManager;
class ResourceManager;
class Pipeline;

class Game
{
public:
	Game();
	~Game();

	shared_ptr<SceneManager> GetSceneManager() { return _sceneManager; }
	shared_ptr<InputManager> GetInputManager() { return _inputManager; }
	shared_ptr<TimeManager> GetTimeManager() { return _timeManager; }
	shared_ptr<ResourceManager> GetResourceManager() { return _resourceManager; }

	shared_ptr<Pipeline> GetPipeline() { return _pipeline; }

public:
	void Init(HWND hwnd);
	void Update();
	void Render();


private:
	HWND _hwnd;
	
	shared_ptr<Graphics> _graphics;
	shared_ptr<Pipeline> _pipeline;

	shared_ptr<SceneManager> _sceneManager;
	shared_ptr<InputManager> _inputManager;
	shared_ptr<TimeManager> _timeManager;

	shared_ptr<ResourceManager> _resourceManager;
};

extern unique_ptr<Game> GGame;
