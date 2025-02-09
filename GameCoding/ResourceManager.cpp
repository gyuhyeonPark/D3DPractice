#include "pch.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Animation.h"

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device)
	: _device(device)
{
}

void ResourceManager::Init()
{
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultTexture();
	CreateDefaultMaterial();
	CreateDefaultAnimation();
}

void ResourceManager::CreateDefaultMesh()
{
	shared_ptr<Mesh> mesh = make_shared<Mesh>(_device);
	mesh->SetName(L"Rectangle");
	mesh->CreateDefaultRectangle();
	Add(mesh->GetName(), mesh);
}

void ResourceManager::CreateDefaultShader()
{
	auto vertexShader = make_shared<VertexShader>(_device);
	vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	auto inputLayout = make_shared<InputLayout>(_device);
	inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());

	auto pixelShader = make_shared<PixelShader>(_device);
	pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	shared_ptr<Shader> shader = make_shared<Shader>();
	shader->SetName(L"Default");
	shader->SetInputLayout(inputLayout);
	shader->SetVertexShader(vertexShader);
	shader->SetPixelShader(pixelShader);
	Add(shader->GetName(), shader);
}

void ResourceManager::CreateDefaultTexture()
{
	{
		shared_ptr<Texture> texture = make_shared<Texture>(_device);
		texture->SetName(L"Skeleton");
		texture->Create(L"Skeleton.png");
		Add(texture->GetName(), texture);
	}
	
	{
		shared_ptr<Texture> texture = make_shared<Texture>(_device);
		texture->SetName(L"Snake");
		texture->Create(L"Snake.bmp");
		Add(texture->GetName(), texture);
	}
}

void ResourceManager::CreateDefaultMaterial()
{
	shared_ptr<Material> material = make_shared<Material>();
	material->SetName(L"Default");
	material->SetShader(Get<Shader>(L"Default"));
	material->SetTexture(Get<Texture>(L"Skeleton"));
	Add(material->GetName(), material);
}

void ResourceManager::CreateDefaultAnimation()
{
	shared_ptr<Animation> animation = make_shared<Animation>();
	animation->SetTexture(Get<Texture>(L"Snake"));
	animation->SetName(L"SnakeAnim");
	animation->SetLoop(true);

	animation->AddKeyFrame(KeyFrame{ Vec2(0.f,0.f), Vec2(100.f, 100.f), 0.1f });
	animation->AddKeyFrame(KeyFrame{ Vec2(100.f,0.f), Vec2(100.f, 100.f), 0.1f });
	animation->AddKeyFrame(KeyFrame{ Vec2(200.f,0.f), Vec2(100.f, 100.f), 0.1f });
	animation->AddKeyFrame(KeyFrame{ Vec2(300.f,0.f), Vec2(100.f, 100.f), 0.1f });

	Add(animation->GetName(), animation);

	// XML
	animation->Save(L"TextAnim.xml");


	shared_ptr<Animation> anim2 = make_shared<Animation>();
	anim2->Load(L"TextAnim.xml");
}
