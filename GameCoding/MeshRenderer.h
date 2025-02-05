#pragma once
#include "Component.h"
#include "RenderManager.h"

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~MeshRenderer();

	virtual void Update() override;

	void Render(shared_ptr<Pipeline> pipeline);

private:
	ComPtr<ID3D11Device> _device;

	friend class RenderManager;

	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;

	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<Texture> _texture1;

private:
	shared_ptr<Pipeline> _pipeline;
};

