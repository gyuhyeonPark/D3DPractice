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
	tinyxml2::XMLDocument doc;

	string pathStr(path.begin(), path.end());
	XMLError error = doc.LoadFile(pathStr.c_str());
	assert(error == XMLError::XML_SUCCESS);

	XMLElement* root = doc.FirstChildElement();
	string nameStr = root->Attribute("Name");
	_name = wstring(nameStr.begin(), nameStr.end());
	
	_loop = root->Attribute("Loop");
	_path = path;

	// Load Texture
	XMLElement* node = root->FirstChildElement();
	for (; node != nullptr; node = node->NextSiblingElement())
	{
		KeyFrame keyframe;

		keyframe.offset.x = node->FloatAttribute("OffsetX");
		keyframe.offset.y = node->FloatAttribute("OffsetY");
		keyframe.size.x = node->FloatAttribute("SizeX");
		keyframe.size.y = node->FloatAttribute("SizeY");
		keyframe.time = node->FloatAttribute("Time");

		AddKeyFrame(keyframe);
	}
}

void Animation::Save(const wstring& path)
{
	tinyxml2::XMLDocument doc;
	XMLElement* root = doc.NewElement("Animation");
	doc.LinkEndChild(root);

	string nameStr(GetName().begin(), GetName().end());
	root->SetAttribute("Name", nameStr.c_str());
	root->SetAttribute("Loop", _loop);
	root->SetAttribute("TexturePath", "TODO");

	for (const auto& keyFrame : _keyFrames)
	{
		XMLElement* node = doc.NewElement("Keyframe");
		root->LinkEndChild(node);
		
		node->SetAttribute("OffsetX", keyFrame.offset.x);
		node->SetAttribute("OffsetY", keyFrame.offset.y);
		node->SetAttribute("SizeX", keyFrame.size.x);
		node->SetAttribute("SizeY", keyFrame.size.y);
		node->SetAttribute("Time", keyFrame.time);
	}

	string pathStr(path.begin(), path.end());
	auto result = doc.SaveFile(pathStr.c_str());
	assert(result == XMLError::XML_SUCCESS);
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
