#pragma once
#include "MBGameObject.h"

namespace MB
{
	class SaberAttack : public GameObject
	{
	public:
		enum class AttackState
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
			SitAttack,
			End,
			StandToSit,
			None,
		};


		SaberAttack();
		virtual ~SaberAttack();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


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

		AttackState GetState() { return state; }

	public:
		AttackState state;

		class Collider* SAcol;
	};
}