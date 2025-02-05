#pragma once
/// <summary>
/// DeviceContext가 핵심.
/// 다른 클래스들은 Device가 생성하지만,
/// DeviceContext는 이들을 맵핑하는 역할을 한다.
/// </summary>

class Texture;

struct PipelineInfo
{
	shared_ptr<InputLayout> inputLayout;
	shared_ptr<VertexShader> vertexShader;
	shared_ptr<PixelShader> pixelShader;
	shared_ptr<RasterizerState> rasterizerState;
	shared_ptr<BlendState> blendState;
	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Pipeline
{
public:
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();

	void UpdatePipeline(PipelineInfo info);

	void SetVertexBuffer(shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(shared_ptr<IndexBuffer> buffer);

	template<typename T>
	void SetConstantBuffer(uint32 slot, uint32 scope, shared_ptr<ConstantBuffer<T>> buffer);

	void SetTexture(uint32 slot, uint32 scope, shared_ptr<Texture> texture);
	void SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> samplerState);

	void Draw(uint32 vertexCount, uint32 startVertexLocation);
	void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation);

private:
	ComPtr<ID3D11DeviceContext> _deviceContext;
	
};

template<typename T>
inline void Pipeline::SetConstantBuffer(uint32 slot, uint32 scope, shared_ptr<ConstantBuffer<T>> buffer)
{
	if (scope & SS_VertexShader)
		_deviceContext->VSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());
	if (scope & SS_PixelShader)
		_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

}
