#include "pch.h"
#include "Game.h"
#include "Graphics.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "SceneManager.h"

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
	SCENE->LoadScene(L"Test");
}

void Game::Update()
{
	_graphics->RenderBegin();

	SCENE->Update();
	
	_graphics->RenderEnd();
}

void Game::Render()
{

}