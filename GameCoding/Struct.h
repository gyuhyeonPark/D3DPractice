#pragma once
#include "Types.h"

struct Vertex
{
	Vec3 position;
	//Color color;
	Vec2 uv;
};

struct TransformData
{
	//Vec3 offset;
	//float dummy;		// ConstantBuffer 생성 시엔 16바이트 정렬 필요 => dummy 값 추가

	Matrix matWorld = Matrix::Identity;
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};