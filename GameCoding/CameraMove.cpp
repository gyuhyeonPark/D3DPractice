#include "pch.h"
#include "CameraMove.h"
#include "GameObject.h"
#include "Transform.h"

void CameraMove::Update()
{
	Vec3 pos = GetTransform()->GetPosition();
	pos.x += 0.01f;
	GetTransform()->SetPosition(pos);
}
