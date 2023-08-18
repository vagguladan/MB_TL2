#pragma once
#include "MBGameObject.h"

namespace MB
{
	class Animator;
	class Rigidbody;
	class Collider;


	class Shiki : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			BackMove,
			Attack,
			Jump_Attack,
			Hit,
			JumpToUp,
			JumpToFall,
			Double_Jump,
			Sit,
			SItAttack,
			End,
			StandToSit,
			None,
		};

		enum class eAttState
		{
			FIRST_SLASH,
			SECOND_SLASH,
			THIRD_SLASH,
			JUMP_FIRST_SLASH,
			JUMP_SECOND_SLASH,
			CROUCH_SLASH,
			NONE,
		};

		Shiki();
		virtual ~Shiki();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void InitAnimation();

		void Idle();
		void Move();
		void BackMove();
		void Attack();
		void Jump_Attack();
		void Hit();
		void JumpToUp();
		void JumpToFall();
		void Double_Jump();
		void Sit();
		void SitAttack();
		void StandToSit();

		void SetState(eState state) { mCurState = state; }
		eState GetState() { return mCurState; }

		void AttackFunc();

	private:
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Collider* mCollider;


		eState mState;
		bool mDoubleJumpCheck;
		bool mShikiFrontMove;
		bool mShikiBackMove;
		bool mShikiDownMove;

		eState mCurState;
		eState mPrvState;
		eAttState mCurAttState;
		eAttState mPrvAttState;
		eDir mDir;
		eDir mPrvDir;
		float mAttTime;
		float mAttDelay;

		UINT mAttCount;
		UINT mImgIdx;

	};
}