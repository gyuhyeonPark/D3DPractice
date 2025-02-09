#include "pch.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Mesh.h"
#include "Animator.h"

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

	_animationDataBuffer = make_shared<ConstantBuffer<AnimationData>>(_device, _deviceContext);
	_animationDataBuffer->Create();

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

void RenderManager::PushAnimationData()
{
	_animationDataBuffer->CopyData(_animationData);
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

		// Animation
		shared_ptr<Animator> animator = obj->GetAnimator();
		if (animator)
		{
			const KeyFrame& keyframe = animator->GetCurrentKeyFrame();
			_animationData.spriteOffset = keyframe.offset;
			_animationData.spriteSize = keyframe.size;
			_animationData.textureSize = animator->GetCurrentAnimation()->GetTextureSize();
			_animationData.useAnimation = 1.f;
			PushAnimationData();

			_pipeline->SetConstantBuffer(2, SS_VertexShader, _animationDataBuffer);
			_pipeline->SetTexture(0, SS_PixelShader, animator->GetCurrentAnimation()->GetTexture());
		}
		else
		{
			_animationData.spriteOffset = Vec2(0.f, 0.f);
			_animationData.spriteSize = Vec2(0.f, 0.f);
			_animationData.textureSize = Vec2(0.f, 0.f);
			_animationData.useAnimation = 0.f;
			PushAnimationData();
			_pipeline->SetConstantBuffer(2, SS_VertexShader, _animationDataBuffer);
			_pipeline->SetTexture(0, SS_PixelShader, meshRenderer->GetTexture());
		}

		PipelineInfo info;
		info.inputLayout = meshRenderer->GetInputLayout();
		info.vertexShader = meshRenderer->GetVertexShader();
		info.pixelShader = meshRenderer->GetPixelShader();
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;
		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(meshRenderer->GetMesh()->GetVertexBuffer());
		_pipeline->SetIndexBuffer(meshRenderer->GetMesh()->GetIndexBuffer());

		_pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraDataBuffer);
		_pipeline->SetConstantBuffer(1, SS_VertexShader, _transformDataBuffer);

		//_pipeline->SetTexture(0, SS_PixelShader, meshRenderer->GetTexture());
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

		_pipeline->DrawIndexed(meshRenderer->GetMesh()->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
