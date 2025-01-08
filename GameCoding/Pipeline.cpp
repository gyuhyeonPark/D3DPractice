#include "pch.h"
#include "Pipeline.h"

Pipeline::Pipeline(ComPtr<ID3D11DeviceContext> deviceContext)
{

}

Pipeline::~Pipeline()
{

}

void Pipeline::UpdatePipeline(PipelineInfo info)
{
	_deviceContext->IASetInputLayout(info.inputLayout->GetComPtr().Get());
	_deviceContext->IASetPrimitiveTopology(info.topology);

	// VS
	if (info.vertexShader)
		_deviceContext->VSSetShader(info.vertexShader->GetComPtr().Get(), nullptr, 0);

	// RS
	if (info.rasterizerState)
		_deviceContext->RSSetState(info.rasterizerState->GetComPtr().Get());

	// PS
	if (info.pixelShader)
		_deviceContext->PSSetShader(info.pixelShader->GetComPtr().Get(), nullptr, 0);

	// OM
	if (info.blendState)
		_deviceContext->OMSetBlendState(info.blendState->GetComPtr().Get(), nullptr, 0xFFFFFFFF);

}

void Pipeline::SetVertexBuffer(shared_ptr<VertexBuffer> buffer)
{
	uint32 stride = buffer->GetStride();
	uint32 offset = buffer->GetOffset();
	_deviceContext->IASetVertexBuffers(0, 1, buffer->GetComPtr().GetAddressOf(), &stride, &offset);
}

void Pipeline::SetIndexBuffer(shared_ptr<IndexBuffer> buffer)
{
	_deviceContext->IASetIndexBuffer(buffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
}
