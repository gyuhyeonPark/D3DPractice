#pragma once
/// <summary>
/// 16 Byte 단위로 정렬 해야한다.
/// Constant Buffer의 기본 메모리 정렬 단위가 16바이트이기 떄문.
/// </summary>
struct TransformData
{
	Matrix matWorld = Matrix::Identity;
};

struct CameraData
{
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};

struct AnimationData
{
	Vec2 spriteOffset;
	Vec2 spriteSize;
	Vec2 textureSize;		// 8 * 3 Byte = 24 => 12Byte 부족
	float useAnimation;
	float padding;
};

