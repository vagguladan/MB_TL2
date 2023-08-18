#include "MBShiki.h"
#include "MBTransform.h"
#include "MBTime.h"
#include "MBResources.h"
#include "MBRigidBody.h"
#include "MBCollider.h"
#include "MBObject.h"
#include "MBInput.h"
#include "MBAnimator.h"

namespace MB
{
	Shiki::Shiki()
		: mCurState(eState::Idle)
		, mPrvState(eState::Idle)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mPrvDir(eDir::None)
		, mAttTime(0.0f)
		, mAttCount(0)
		, mAttDelay(0.4f)
		, mImgIdx(0)
		, mShikiFrontMove(nullptr)
		, mShikiBackMove(nullptr)
		, mShikiDownMove(nullptr)
	{
		Vector2 myPos = GetComponent<Transform>()->GetPosition();
	}
	Shiki::~Shiki()
	{
	}
	void Shiki::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mRigidbody = AddComponent<Rigidbody>();
		mCollider = AddComponent<Collider>();

		mCollider->SetSize(Vector2(-200.0f, 400.0f));
		mCollider->SetOffset(Vector2(0.0f, 25.0f));
		mAnimator->SetScale(Vector2(1.0f, 1.0f));


		InitAnimation();
		mAnimator->PlayAnimation(L"Shiki_Idle", true);
		mCurState = eState::Idle;
	}
	void Shiki::InitAnimation()
	{
		Animator* at2 = GetComponent<Animator>();

		at2->CreateAnimationFolder(L"Shiki_Idle", L"..\\Resources\\Image\\Player\\Shiki\\Standing", Vector2(0.0f, -60.0f), 0.2f);
		at2->CreateAnimationFolder(L"Shiki_AAttack", L"..\\Resources\\Image\\Player\\Shiki\\AAttack", Vector2(0.0f, -60.0f), 0.08f);
		at2->CreateAnimationFolder(L"Shiki_BAttack", L"..\\Resources\\Image\\Player\\Shiki\\BAttack", Vector2(0.0f, -60.0f), 0.08f);
		at2->CreateAnimationFolder(L"Shiki_CAttack", L"..\\Resources\\Image\\Player\\Shiki\\CAttack", Vector2(0.0f, -60.0f), 0.08f);
		at2->CreateAnimationFolder(L"Shiki_JumpAAttack", L"..\\Resources\\Image\\Player\\Shiki\\JumpAAttack", Vector2(0.0f, -60.0f), 0.1f);
		at2->CreateAnimationFolder(L"Shiki_JumpBAttack", L"..\\Resources\\Image\\Player\\Shiki\\JumpBAttack", Vector2(0.0f, -60.0f), 0.1f);
		at2->CreateAnimationFolder(L"Shiki_JumpCAttack", L"..\\Resources\\Image\\Player\\Shiki\\JumpCAttack", Vector2(0.0f, -60.0f), 0.1f);
		at2->CreateAnimationFolder(L"Shiki_BackJump", L"..\\Resources\\Image\\Player\\Shiki\\BackJump", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_Sit", L"..\\Resources\\Image\\Player\\Shiki\\Sit", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_SitAAttack", L"..\\Resources\\Image\\Player\\Shiki\\SitAAttack", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_SitBAttack", L"..\\Resources\\Image\\Player\\Shiki\\SitBAttack", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_SitCAttack", L"..\\Resources\\Image\\Player\\Shiki\\SitCAttack", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_StandtoSit", L"..\\Resources\\Image\\Player\\Shiki\\StandToSit", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_JumpToUp", L"..\\Resources\\Image\\Player\\Shiki\\JumpUp", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_JumpToDown", L"..\\Resources\\Image\\Player\\Shiki\\JumpDown", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_FrontMove", L"..\\Resources\\Image\\Player\\Shiki\\FrontMove", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_BackMove", L"..\\Resources\\Image\\Player\\Shiki\\BackMove", Vector2(0.0f, -60.0f));

		at2->CreateAnimationFolder(L"Shiki_StandHit", L"..\\Resources\\Image\\Player\\Shiki\\StandHit", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_SitHit", L"..\\Resources\\Image\\Player\\Shiki\\SitHit", Vector2(0.0f, -60.0f));
		at2->CreateAnimationFolder(L"Shiki_DashMove", L"..\\Resources\\Image\\Player\\Shiki\\DashMove", Vector2(0.0f, -60.0f));

	}
	void Shiki::Update()
	{

		GameObject::Update();

		switch (mState)
		{
		case MB::Shiki::eState::Idle:
			Idle();
			break;
		case MB::Shiki::eState::Move:
			Move();
			break;
		case MB::Shiki::eState::Double_Jump:
			Double_Jump();
			break;
		case MB::Shiki::eState::Attack:
			Attack();
			break;
		case MB::Shiki::eState::Jump_Attack:
			Jump_Attack();
			break;
		case MB::Shiki::eState::JumpToUp:
			JumpToUp();
			break;
		case MB::Shiki::eState::JumpToFall:
			JumpToFall();
			break;
		case MB::Shiki::eState::Hit:
			Hit();
			break;
		case MB::Shiki::eState::End:
			break;
		case MB::Shiki::eState::Sit:
			Sit();
			break;
		case MB::Shiki::eState::SItAttack:
			SitAttack();
			break;
		case MB::Shiki::eState::StandToSit:
			StandToSit();
			break;
		default:
			break;
		}
	}
	void Shiki::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void Shiki::Idle()
	{
		Animator* animator = GetComponent<Animator>();
		mShikiDownMove = false;
		mDoubleJumpCheck = false;

		mCollider->SetSize(Vector2(-200.0f, 400.0f));
		mCollider->SetOffset(Vector2(0.0f, 25.0f));

		if (Input::GetKeyDown(eKeyCode::Up))
		{
			animator->PlayAnimation(L"Shiki_JumpToUp", false);
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);

			mState = eState::JumpToUp;
		}

		if (Input::GetKey(eKeyCode::Right))
		{


			animator->PlayAnimation(L"Shiki_BackMove", true);
			mState = eState::Move;
			mShikiBackMove = true;
		}
		if (Input::GetKey(eKeyCode::Down))
		{
			animator->PlayAnimation(L"Shiki_Sit", true);
			mState = eState::Sit;
		}
		if (Input::GetKey(eKeyCode::Left))
		{
			animator->PlayAnimation(L"Shiki_FrontMove", true);
			mState = eState::Move;
		}


		if (Input::GetKey(eKeyCode::NUM1))
		{

			animator->PlayAnimation(L"Shiki_AAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKey(eKeyCode::NUM2))
		{
			animator->PlayAnimation(L"Shiki_BAttack", false);
			mState = eState::Attack;
		}
		if (Input::GetKey(eKeyCode::NUM3))
		{
			animator->PlayAnimation(L"Shiki_CAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKey(eKeyCode::H) && mShikiDownMove == true && mShikiFrontMove == true)
		{
			Transform* tr = GetComponent<Transform>();
		}



	}
	void Shiki::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		AttackFunc();

		if (Input::GetKeyDown(eKeyCode::Up))
		{
			animator->PlayAnimation(L"Shiki_JumpToUp", false);
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);

			mState = eState::JumpToUp;
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
			mShikiFrontMove = true;
		}
		if (Input::GetKey(eKeyCode::Down))
		{
			//if (pos.y < 480.0f)
			//pos.y += 300.0f * Time::DeltaTime();

			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 300.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}
		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::Up)
			|| Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Down)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			Animator* animator = GetComponent<Animator>();
			animator->PlayAnimation(L"Shiki_Idle", true);
			mState = eState::Idle;
			
		}

		if (Input::GetKey(eKeyCode::NUM1))
		{


			animator->PlayAnimation(L"Shiki_AAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKey(eKeyCode::NUM2))
		{
			animator->PlayAnimation(L"Shiki_BAttack", false);
			mState = eState::Attack;
		}
		if (Input::GetKey(eKeyCode::NUM3))
		{
			animator->PlayAnimation(L"Shiki_CAttack", false);
			mState = eState::Attack;
		}

	}
	void Shiki::BackMove()
	{

		Transform* tr = GetComponent<Transform>();
		Vector2 velocity = mRigidbody->GetVelocity();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		mShikiBackMove = true;

		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKeyDown(eKeyCode::NUM1) || Input::GetKeyDown(eKeyCode::NUM2) || Input::GetKeyDown(eKeyCode::NUM3))
		{
			mCurState = eState::Attack;
		}

		if (Input::GetKeyUp(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"Shiki_Idle", true);
			mState = eState::Idle;
		}

		if (Input::GetKey(eKeyCode::NUM1))
		{


			animator->PlayAnimation(L"Shiki_AAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKey(eKeyCode::NUM2))
		{
			animator->PlayAnimation(L"Shiki_BAttack", false);
			mState = eState::Attack;
		}
		if (Input::GetKey(eKeyCode::NUM3))
		{
			animator->PlayAnimation(L"Shiki_CAttack", false);
			mState = eState::Attack;
		}
	}
	void Shiki::Attack()
	{
		Animator* animator = GetComponent<Animator>();
		if (mShikiDownMove == true)
		{
			if (animator->IsActiveAnimationComplete())
			{
				animator->PlayAnimation(L"Shiki_Sit", true);
				mState = eState::Sit;
			}
		}
		if (mShikiDownMove == false)
		{
			if (animator->IsActiveAnimationComplete())
			{
				animator->PlayAnimation(L"Shiki_Idle", true);
				mState = eState::Idle;
			}

		}
	}
	void Shiki::Jump_Attack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();

		if (animator->IsActiveAnimationComplete())
		{
			if (rb->GetGround() != false)
			{
				animator->PlayAnimation(L"Shiki_JumpToDown", true);
				mState = eState::JumpToFall;
			}


			if (rb->GetGround() == true)
			{
				animator->PlayAnimation(L"Shiki_Idle", true);
				mState = eState::Idle;

			}
			mDoubleJumpCheck = false;
		}
	}
	void Shiki::Hit()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"Shiki_Idle", true);
			mState = eState::Idle;
		}
	}
	void Shiki::JumpToUp()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyDown(eKeyCode::Up) && mDoubleJumpCheck == false)
		{
			animator->PlayAnimation(L"Shiki_JumpToUp", false);
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);

			mDoubleJumpCheck = true;
			mState = eState::JumpToFall;
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::Down))
		{

			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::NUM1))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Shiki_JumpAAttack", false);
			mState = eState::Jump_Attack;
		}

		if (Input::GetKey(eKeyCode::NUM2))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Shiki_JumpBAttack", false);
			mState = eState::Jump_Attack;
		}
		if (Input::GetKey(eKeyCode::NUM3))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Shiki_JumpCAttack", false);
			mState = eState::Jump_Attack;
		}

		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"Shiki_JumpToDown", true);
			mState = eState::JumpToFall;
		}
	}
	void Shiki::JumpToFall()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();

		if (rb->GetGround() != false)
		{
			animator->PlayAnimation(L"Shiki_JumpToDown", true);


		}
		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			//GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			//GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}

		if (Input::GetKey(eKeyCode::NUM1))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Shiki_JumpAAttack", false);
			mState = eState::Jump_Attack;
		}

		if (Input::GetKey(eKeyCode::NUM2))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Shiki_JumpBAttack", false);
			mState = eState::Jump_Attack;
		}
		if (Input::GetKey(eKeyCode::NUM3))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Shiki_JumpCAttack", false);
			mState = eState::Jump_Attack;
		}

		if (rb->GetGround() == true)
		{
			animator->PlayAnimation(L"Shiki_Idle", true);
			mState = eState::Idle;

		}
	}
	void Shiki::Double_Jump()
	{

	}
	void Shiki::Sit()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		mShikiDownMove = true;

		mCollider->SetSize(Vector2(-200.0f, 300.0f));
		mCollider->SetOffset(Vector2(0.0f, 73.0f));


		if (Input::GetKey(eKeyCode::NUM1))
		{
			Transform* tr = GetComponent<Transform>();


			animator->PlayAnimation(L"Shiki_SitAAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKey(eKeyCode::NUM2))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Shiki_SitBAttack", false);
			mState = eState::Attack;
		}
		if (Input::GetKey(eKeyCode::NUM3))
		{
			Transform* tr = GetComponent<Transform>();


			animator->PlayAnimation(L"Shiki_SitCAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKeyUp(eKeyCode::Down))
		{
			Animator* animator = GetComponent<Animator>();
			animator->PlayAnimation(L"Shiki_Idle", true);
			mState = eState::Idle;
		}
	}
	void Shiki::SitAttack()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"Shiki_Idle", true);
			mState = eState::Idle;
		}
	}
	void Shiki::StandToSit()
	{
	}
	void Shiki::AttackFunc()
	{
	}

	void Shiki::OnCollisionEnter(Collider* other)
	{
	}
	void Shiki::OnCollisionStay(Collider* other)
	{
	}
	void Shiki::OnCollisionExit(Collider* other)
	{
	}
}