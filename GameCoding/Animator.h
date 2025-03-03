#pragma once
#include "Component.h"
#include "Animation.h"

class Animator : public Component
{
	using Super = Component;

public:
	Animator();
	~Animator();

	void Init();
	void Update();

	shared_ptr<Animation> GetCurrentAnimation();
	const KeyFrame& GetCurrentKeyFrame();

	void SetAnimation(shared_ptr<Animation> animation) { _currentAnimation = animation; }

private:
	float _sumTime = 0.f;
	int32 _currentKeyFrameIndex = 0;

	shared_ptr<Animation> _currentAnimation;
};

