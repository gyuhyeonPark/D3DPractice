#pragma once
/// <summary>
/// 16 Byte ������ ���� �ؾ��Ѵ�.
/// Constant Buffer�� �⺻ �޸� ���� ������ 16����Ʈ�̱� ����.
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
	Vec2 textureSize;		// 8 * 3 Byte = 24 => 12Byte ����
	float useAnimation;
	float padding;
};

