#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: _device(device)
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

	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
	_constantBuffer->Create(); 
	
	_texture1 = make_shared<Texture>(device);
	_texture1->Create(L"Skeleton.png");
	
	_samplerState = make_shared<SamplerState>(device);
	_samplerState->Create();

	_transform->SetLocalPosition(Vec3(1.5f,0.f,0.f));

}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	_transformData.matWorld = _transform->GetWorldMatrix();
	_constantBuffer->CopyData(_transformData);
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
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
	pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
