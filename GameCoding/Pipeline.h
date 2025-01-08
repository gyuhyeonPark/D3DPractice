#pragma once
/// <summary>
/// DeviceContext가 핵심.
/// 다른 클래스들은 Device가 생성하지만,
/// DeviceContext는 이들을 맵핑하는 역할을 한다.
/// </summary>

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
	void SetConstantBuffer(uint32 slot, shared_ptr<ConstantBuffer<T>> buffer);

private:
	ComPtr<ID3D11DeviceContext> _deviceContext;
	
};

template<typename T>
inline void Pipeline::SetConstantBuffer(uint32 slot, shared_ptr<ConstantBuffer<T>> buffer)
{
	_deviceContext->VSSetConstantBuffers(slot, 1, _constantBuffer->GetComPtr().GetAddressOf());

}
