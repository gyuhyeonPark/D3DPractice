#pragma once

struct TransformData
{
	Matrix matWorld = Matrix::Identity;
};

struct CameraData
{
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};

