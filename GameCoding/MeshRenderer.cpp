#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext, shared_ptr<Pipeline> pipeline)
	: Super(ComponentType::MeshRenderer), _device(device), _pipeline(pipeline)
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	_vertexBuffer = make_shared<VertexBuffer>(device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(device);
	_indexBuffer->Create(_geometry->GetIndices());

	_vertexShader = make_shared<VertexShader>(device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	_inputLayout = make_shared<InputLayout>(device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

	_pixelShader = make_shared<PixelShader>(device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	_rasterizerState = make_shared<RasterizerState>(device);
	_rasterizerState->Create();

	_blendState = make_shared<BlendState>(device);
	_blendState->Create();

	_cameraDataBuffer = make_shared<ConstantBuffer<CameraData>>(device, deviceContext);
	_cameraDataBuffer->Create();

	_transformDataBuffer = make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
	_transformDataBuffer->Create();

	_texture1 = make_shared<Texture>(device);
	_texture1->Create(L"Skeleton.png");

	_samplerState = make_shared<SamplerState>(device);
	_samplerState->Create();

}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{
	//_cameraData.matView = Matrix::Identity;
	//_cameraData.matProjection = Matrix::Identity;
	_cameraData.matView = Camera::S_MatView;
	_cameraData.matProjection = Camera::S_MatProjection;

	_cameraDataBuffer->CopyData(_cameraData);

	_transformData.matWorld = GetTransform()->GetWorldMatrix();
	_transformDataBuffer->CopyData(_transformData);

	// TEMP
	Render(_pipeline);
}

void MeshRenderer::Render(shared_ptr<Pipeline> pipeline)
{
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;
	pipeline->UpdatePipeline(info);

	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetIndexBuffer(_indexBuffer);

	pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraDataBuffer);
	pipeline->SetConstantBuffer(1, SS_VertexShader, _transformDataBuffer);

	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
