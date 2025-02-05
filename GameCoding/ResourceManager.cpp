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
}

void ResourceManager::CreateDefaultShader()
{
}

void ResourceManager::CreateDefaultTexture()
{
	shared_ptr<Texture> texture = make_shared<Texture>(_device);
	texture->SetName(L"Skeleton");
	texture->Create(L"Skeleton.png");
	Add<Texture>(texture->GetName(), texture);
}

void ResourceManager::CreateDefaultMaterial()
{
}

void ResourceManager::CreateDefaultAnimation()
{
}
