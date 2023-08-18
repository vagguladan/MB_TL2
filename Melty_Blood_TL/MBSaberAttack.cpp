#include "MBSaberAttack.h"
#include "MBInput.h"
#include "MBTime.h"
#include "MBCollider.h"
#include "MBTransform.h"

#include "MBShiki.h"
#include "MBAnimator.h"


namespace MB
{
	SaberAttack::SaberAttack():
		state(SaberAttack::AttackState::Idle)
	{
	}
	SaberAttack::~SaberAttack()
	{
	}
	void SaberAttack::Initialize()
	{
	}
	void SaberAttack::Update()
	{

		GameObject::Update();

		switch (state)
		{
		case::MB::SaberAttack::AttackState::Idle:
				Idle();
				break;
		case::MB::SaberAttack::AttackState::Move:
			Move();
			break;
		case::MB::SaberAttack::AttackState::Attack:
			Attack();
			break;
		case::MB::SaberAttack::AttackState::Jump_Attack:
			Jump_Attack();
			break;
		case::MB::SaberAttack::AttackState::Hit:
			Hit();
			break;
		case::MB::SaberAttack::AttackState::JumpToUp:
			JumpToUp();
			break;
		case::MB::SaberAttack::AttackState::JumpToFall:
			JumpToFall();
			break;
		case::MB::SaberAttack::AttackState::Double_Jump:
			Double_Jump();
			break;
		case::MB::SaberAttack::AttackState::Sit:
			Sit();
			break;
		case::MB::SaberAttack::AttackState::SitAttack:
			SitAttack();
			break;
		case::MB::SaberAttack::AttackState::StandToSit:
			StandToSit();
			break;


		}


	}
	void SaberAttack::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SaberAttack::OnCollisionEnter(Collider* other)
	{
		Shiki* shiki = dynamic_cast<Shiki*>(other->GetOwner());
		if (shiki == nullptr)
			return;
		Transform* Str = shiki->GetComponent<Transform>();
		Vector2 pos = Str->GetPosition();

		Animator* Shiki_Hit = shiki->GetComponent<Animator>();
		Shiki_Hit->PlayAnimation(L"Shiki_StandHit");
	}
	void SaberAttack::OnCollisionStay(Collider* other)
	{
	}
	void SaberAttack::OnCollisionExit(Collider* other)
	{
	}
	void SaberAttack::Idle()
	{

	}
	void SaberAttack::Move()
	{
	}
	void SaberAttack::BackMove()
	{
	}
	void SaberAttack::Attack()
	{

	}
	void SaberAttack::Jump_Attack()
	{
	}
	void SaberAttack::Hit()
	{
	}
	void SaberAttack::JumpToUp()
	{
	}
	void SaberAttack::JumpToFall()
	{
	}
	void SaberAttack::Double_Jump()
	{
	}
	void SaberAttack::Sit()
	{
	}
	void SaberAttack::SitAttack()
	{
	}
	void SaberAttack::StandToSit()
	{
	}
}