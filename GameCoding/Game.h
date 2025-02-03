#pragma once

class Graphics;
class GameObject;
class SceneManager;
class Pipeline;

class Game
{
public:
	Game();
	~Game();

	shared_ptr<SceneManager> GetSceneManager() { return _sceneManager; }

public:
	void Init(HWND hwnd);
	void Update();
	void Render();


private:
	HWND _hwnd;
	
	shared_ptr<Graphics> _graphics;
	shared_ptr<Pipeline> _pipeline;

	shared_ptr<SceneManager> _sceneManager;
};

extern unique_ptr<Game> GGame;
