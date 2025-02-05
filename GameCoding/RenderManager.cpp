#include "pch.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Scene.h"
#include "SceneManager.h"

RenderManager::RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: _device(device), _deviceContext(deviceContext)
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::Init()
{
	_pipeline = make_shared<Pipeline>(_deviceContext);

	_cameraDataBuffer = make_shared<ConstantBuffer<CameraData>>(_device, _deviceContext);
	_cameraDataBuffer->Create();

	_transformDataBuffer = make_shared<ConstantBuffer<TransformData>>(_device, _deviceContext);
	_transformDataBuffer->Create();

	_rasterizerState = make_shared<RasterizerState>(_device);
	_rasterizerState->Create();

	_blendState = make_shared<BlendState>(_device);
	_blendState->Create();

	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->Create();
}

void RenderManager::Update(shared_ptr<Graphics> graphics)
{
	graphics->RenderBegin();

	PushCameraData();
	GatherRenderableObjects();
	RenderObjects();

	graphics->RenderEnd();
}

void RenderManager::PushCameraData()
{
	_cameraData.matView = Camera::S_MatView;
	_cameraData.matProjection = Camera::S_MatProjection;

	_cameraDataBuffer->CopyData(_cameraData);
}

void RenderManager::PushTransformData()
{
	_transformDataBuffer->CopyData(_transformData);
}

void RenderManager::GatherRenderableObjects()
{
	_renderObjects.clear();

	auto& gameObjects = SCENE->GetActiveScene()->GetGameObjects();
	for (const shared_ptr<GameObject>& obj : gameObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer = obj->GetMeshRenderer();
		if (meshRenderer)
			_renderObjects.push_back(obj);
	}

}

void RenderManager::RenderObjects()
{
	for (const shared_ptr<GameObject>& obj : _renderObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer = obj->GetMeshRenderer();
		if (!meshRenderer)
			continue;

		shared_ptr<Transform> transform = obj->GetTransform();
		if (!transform)
			continue;

		// SRT
		_transformData.matWorld = transform->GetWorldMatrix();
		PushTransformData();

		PipelineInfo info;
		info.inputLayout = meshRenderer->_inputLayout;
		info.vertexShader = meshRenderer->_vertexShader;
		info.pixelShader = meshRenderer->_pixelShader;
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;
		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(meshRenderer->_vertexBuffer);
		_pipeline->SetIndexBuffer(meshRenderer->_indexBuffer);

		_pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraDataBuffer);
		_pipeline->SetConstantBuffer(1, SS_VertexShader, _transformDataBuffer);

		_pipeline->SetTexture(0, SS_PixelShader, meshRenderer->_texture1);
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

		_pipeline->DrawIndexed(meshRenderer->_geometry->GetIndexCount(), 0, 0);
	}
}
