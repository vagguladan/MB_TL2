#include "MBAnimation.h"
#include "MBTexture.h"
#include "MBAnimator.h"
#include "MBTime.h"
#include "MBTransform.h"
#include "MBGameObject.h"
#include "MBCamera.h"

namespace MB
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mTexture(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			//_mTime = 0.0f; 
			mTime = mTime - mSpriteSheet[mIndex].duration;

			if (mIndex < mSpriteSheet.size() - 1)
				mIndex++;
			else
				mbComplete = true;
		}
	}
	void Animation::Render(HDC hdc)
	{

		if (mTexture == nullptr)
			return;

		Sprite sprite = mSpriteSheet[mIndex];

		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Animator* animator = mAnimator;

		mTexture->Render(hdc
			, pos
			, sprite.Size
			, sprite.LeftTop
			, sprite.Size
			, sprite.Offset
			, animator->GetScale()
			, animator->GetAlpha())
			, tr->GetRotation();

	}
	void Animation::Create(const std::wstring& name, Texture* texture,
		Vector2 leftTop, Vector2 size, 
		Vector2 offset, UINT spriteLength, float duration)

	{
		mTexture = texture;

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};

			sprite.LeftTop.x = leftTop.x + (size.x * i);
			sprite.LeftTop.y = leftTop.y;
			// 아랫줄로 이어서 실행할때
			if (sprite.LeftTop.x >= texture->GetWidth())
			{
				sprite.LeftTop.x = sprite.LeftTop.x - texture->GetWidth();
				sprite.LeftTop.y = leftTop.y + size.y;
			}
			sprite.Size = size;
			sprite.Offset = offset;
			sprite.duration = duration;

			mSpriteSheet.push_back(sprite);
		}

	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}