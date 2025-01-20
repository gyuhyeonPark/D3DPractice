#pragma once

#include "Types.h"
#include "Values.h"
#include "Struct.h"

// STL
#include <vector>
#include <array>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

// WIN
#include <windows.h>
#include <assert.h>

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
/// 프로젝트 설정 -> 추가 포함 디렉터리로 경로를 설정, 해당 경로의 헤더 및 인라인 파일을 체크해서 가능한 것.
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")
#endif

#define CHECK(p)	assert(SUCCEEDED(p))

// Engine
// 원래는 이런식으로 때려버리면 안되고, 꼭 헤더에 전방선언 및 cpp에 #include 해주는 것이 정석이다.
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "Geometry.h"
#include "GeometryHelper.h"
#include "VertexData.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"
#include "Pipeline.h"
