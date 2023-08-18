#pragma once
#include "MBGameObject.h"
#include "MBSaber.h"
#include "MBAnimator.h"

namespace MB
{
	class Animator;
	class Collider;
	class Transform;


	class SaberHitBox : public GameObject
	{
	public:
		SaberHitBox();
		virtual ~SaberHitBox();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		void SetOwner(Saber* owner) { mSaber = owner; }

	private:

		Saber* mSaber;
		float mTime;

	private:

		Animator* mAnimator;
		Collider* mCollider;
		Transform* mTransform;
	};
}