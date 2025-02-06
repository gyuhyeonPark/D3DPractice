#pragma once
#include "ResourceBase.h"

class Shader : public ResourceBase
{
	using Super = ResourceBase;

public:
	Shader();
	virtual ~Shader();

	shared_ptr<InputLayout>		  GetInputLayout() { return _inputLayout; }
	shared_ptr<VertexShader>	  GetVertexShader() { return _vertexShader; }
	shared_ptr<PixelShader>		  GetPixelShader() { return _pixelShader; }

	void SetInputLayout(shared_ptr<InputLayout> layout) { _inputLayout = layout; }
	void SetVertexShader(shared_ptr<VertexShader> vertexShader) { _vertexShader = vertexShader; }
	void SetPixelShader(shared_ptr<PixelShader> pixelShader) { _pixelShader = pixelShader; }

private:
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<PixelShader> _pixelShader;
	
};

