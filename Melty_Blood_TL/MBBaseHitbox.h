#pragma once
#include "MBGameObject.h"
#include "MBAnimator.h"
#include "MBSaber.h"

namespace MB
{
	class Animator;
	class Collider;


	class HitBox : public GameObject
	{
	public:
		HitBox();
		virtual ~HitBox();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		__forceinline void SetPlayer(Saber* saber)
		{

			mSaber = saber;
		}
		__forceinline GameObject* GetOwner() { return mSaber; }
		void SlashCollider();

	private:
		Animator* mAnimator;
		Collider* mCollider;
		Saber* mSaber;

		float mTime;
	};
}