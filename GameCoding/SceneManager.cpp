#include "pch.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Pipeline.h"
#include "Mesh.h"
#include "Animator.h"
#include "Transform.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics)
	: _graphics(graphics)
{
}

void SceneManager::Init()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();

	_activeScene->FixedUpdate();
}

void SceneManager::LoadScene(wstring sceneName)
{
	// TEMP
	LoadTestScene();
	Init();
}

#include "CameraMove.h"
shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();
	
	// Camera
	{
		shared_ptr<GameObject> _camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			_camera->GetOrAddTransform();
			_camera->AddComponent(make_shared<Camera>());

			_camera->AddComponent(make_shared<CameraMove>());

			scene->AddGameObject(_camera);			
		}
	}


	// Monster
	{
		shared_ptr<GameObject> monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		monster->GetOrAddTransform()->SetPosition(Vec3(1.f, 1.f, 0.f));
		{
			monster->GetOrAddTransform();
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			monster->AddComponent(meshRenderer);
			auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);
			auto material = RESOURCE->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);
		}
		{
			auto animator = make_shared<Animator>();
			monster->AddComponent(animator);
			auto anim = RESOURCE->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(monster);
	}

	// Monster
	{
		shared_ptr<GameObject> monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			monster->GetOrAddTransform();
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			monster->AddComponent(meshRenderer);
			auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);
			auto material = RESOURCE->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);
		}
		{
			auto animator = make_shared<Animator>();
			monster->AddComponent(animator);
			auto anim = RESOURCE->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(monster);
	}

	_activeScene = scene;
	return _activeScene;
}
