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
	float dummy;		// ConstantBuffer ���� �ÿ� 16����Ʈ ���� �ʿ� => dummy �� �߰�
};