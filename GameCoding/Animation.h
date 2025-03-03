#pragma once
#include "ResourceBase.h"

struct KeyFrame
{
    Vec2 offset = Vec2{ 0.0f, 0.0f };
    Vec2 size = Vec2{ 0.0f, 0.0f };
    float time = 0.0f;
};

class Texture;

class Animation : public ResourceBase
{
    using Super = ResourceBase;

public:
    Animation();
    virtual ~Animation();
   
    virtual void Load(const wstring& path) override;
    virtual void Save(const wstring& path) override;

    void SetLoop(bool loop) { _loop = loop; }
    bool IsLoop() { return _loop; }
    
    void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }
    shared_ptr<Texture> GetTexture() { return _texture; }
    Vec2 GetTextureSize();

    const KeyFrame& GetKeyFrame(int32 index);
    int32 GetKeyFrameCount();
    void AddKeyFrame(const KeyFrame& keyFrame);

private:
    bool _loop = false;
    shared_ptr<Texture> _texture;
    vector<KeyFrame> _keyFrames;
};

