#include "pch.h"
#include "Animation.h"
#include "Texture.h"

Animation::Animation()
	: Super(ResourceType::Animation)
{
}

Animation::~Animation()
{
}

void Animation::Load(const wstring& path)
{
}

void Animation::Save(const wstring& path)
{
}

Vec2 Animation::GetTextureSize()
{
	return _texture->GetSize();
}

const KeyFrame& Animation::GetKeyFrame(int32 index)
{
	return _keyFrames[index];
}

int32 Animation::GetKeyFrameCount()
{
	return static_cast<int32>(_keyFrames.size());
}

void Animation::AddKeyFrame(const KeyFrame& keyFrame)
{
	_keyFrames.push_back(keyFrame);
}
