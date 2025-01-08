#pragma once
#include "Types.h"

struct TransformData
{
	//Vec3 offset;
	//float dummy;		// ConstantBuffer ���� �ÿ� 16����Ʈ ���� �ʿ� => dummy �� �߰�

	Matrix matWorld = Matrix::Identity;
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};