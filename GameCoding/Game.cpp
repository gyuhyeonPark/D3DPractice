#include "pch.h"
#include "Game.h"
#include "Graphics.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"

unique_ptr<Game> GGame = make_unique<Game>();

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_graphics = make_shared<Graphics>(hwnd);
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());

	_sceneManager = make_shared<SceneManager>(_graphics);
	_sceneManager->Init();

	_inputManager = make_shared<InputManager>();
	_inputManager->Init(hwnd);

	_timeManager = make_shared<TimeManager>();
	_timeManager->Init();

	_resourceManager = make_shared<ResourceManager>(_graphics->GetDevice());
	_resourceManager->Init();

	SCENE->LoadScene(L"Test");
}

void Game::Update()
{
	_graphics->RenderBegin();

	SCENE->Update();
	INPUT->Update();
	TIME->Update();

	_graphics->RenderEnd();
}

void Game::Render()
{
	
}