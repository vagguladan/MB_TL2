#pragma once
#include "MBResource.h"

namespace MB
{
	using namespace math;
	class Texture;
	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 LeftTop;
			Vector2 Size;
			Vector2 Offset;
			float duration;

			Sprite()
				: LeftTop(Vector2::Zero)
				, Size(Vector2::Zero)
				, Offset(Vector2::Zero)
				,duration(0.0f)
			{}
		};

		Animation();
		~Animation();
		void Update();
		void Render(HDC hdc);

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		void Create(const std::wstring& name
			, class Texture* texture
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLength, float duration);

		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

		void SetIndex(int idx) { mIndex = idx; }
		int GetIndex() { return mIndex; }

	private:
		Animator* mAnimator;
		Texture* mTexture;

		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}