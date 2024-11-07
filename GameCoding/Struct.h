#pragma once
#include "Types.h"

struct Vertex
{
	Vec3 postion;
	//Color color;
	Vec2 uv;
};

struct TransformData
{
	Vec3 offset;
	float dummy;		// ConstantBuffer 생성 시엔 16바이트 정렬 필요 => dummy 값 추가
};