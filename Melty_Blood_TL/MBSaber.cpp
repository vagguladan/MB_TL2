#include "MBSaber.h"
#include "MBTransform.h"
#include "MBTime.h"
#include "MBResources.h"
#include "MBAnimator.h"
#include "MBRigidBody.h"
#include "MBCollider.h"
#include "MBObject.h"
#include "MBInput.h"
#include "MBCollisionManager.h"
#include "MBBaseHitbox.h"
#include "MBShiki.h"

namespace MB
{
	Saber::Saber()
		: mCurState(eState::Idle)
		, mPrvState(eState::Idle)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mHitbox(nullptr)
		, mPrvDir(eDir::None)
		, mAttTime(0.0f)
		, mAttCount(0)
		, mAttDelay(0.4f)
		, mImgIdx(0)
		, mSaber_Attack(Saber_Attack::None)
		, mSaberFrontMove(nullptr)
		, mSaberBackMove(nullptr)
		, mSaberDownMove(nullptr)
	{
		Vector2 myPos = GetComponent<Transform>()->GetPosition();

	}
	Saber::~Saber()
	{
	}
	void Saber::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mRigidbody = AddComponent<Rigidbody>();
		mCollider = AddComponent<Collider>();
		mHitbox = AddComponent<Collider>();

		
		mCollider->SetSize(Vector2(-200.0f, 400.0f));
		mCollider->SetOffset(Vector2(0.0f, 25.0f));

		mAnimator->SetScale(Vector2(1.0f, 1.0f));

		InitAnimation();
		mAnimator->PlayAnimation(L"Saber_Idle", true);
		mCurState = eState::Idle;

	

	}
	void Saber::InitAnimation()
	{

		Animator* at = GetComponent<Animator>();

		at->CreateAnimationFolder(L"Saber_Idle", L"..\\Resources\\Image\\Player\\Saber\\Standing", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_AAttack", L"..\\Resources\\Image\\Player\\Saber\\AAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_BAttack", L"..\\Resources\\Image\\Player\\Saber\\BAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_CAttack", L"..\\Resources\\Image\\Player\\Saber\\CAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpAAttack", L"..\\Resources\\Image\\Player\\Saber\\JumpAAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpBAttack", L"..\\Resources\\Image\\Player\\Saber\\JumpBAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpCAttack", L"..\\Resources\\Image\\Player\\Saber\\JumpCAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_BackJump", L"..\\Resources\\Image\\Player\\Saber\\BackJump", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_Sit", L"..\\Resources\\Image\\Player\\Saber\\Sit", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_SitAAttack", L"..\\Resources\\Image\\Player\\Saber\\SitAAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_SitBAttack", L"..\\Resources\\Image\\Player\\Saber\\SitBAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_SitCAttack", L"..\\Resources\\Image\\Player\\Saber\\SitCAttack", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_StandtoSit", L"..\\Resources\\Image\\Player\\Saber\\StandToSit", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpToUp", L"..\\Resources\\Image\\Player\\Saber\\JumpUp", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_JumpToDown", L"..\\Resources\\Image\\Player\\Saber\\JumpDown", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_FrontMove", L"..\\Resources\\Image\\Player\\Saber\\FrontMove", Vector2(0.0f, -60.0f));
		at->CreateAnimationFolder(L"Saber_BackMove", L"..\\Resources\\Image\\Player\\Saber\\BackMove", Vector2(0.0f, -60.0f));

	}

	void Saber::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case MB::Saber::eState::Idle:
			Idle();
			break;
		case MB::Saber::eState::Move:
			Move();
			break;
		case MB::Saber::eState::Double_Jump:
			Double_Jump();
			break;
		case MB::Saber::eState::Attack:
			Attack();
			break;
		case MB::Saber::eState::Jump_Attack:
			Jump_Attack();
			break;
		case MB::Saber::eState::JumpToUp:
			JumpToUp();
			break;
		case MB::Saber::eState::JumpToFall:
			JumpToFall();
			break;
		case MB::Saber::eState::Hit:
			Hit();
			break;
		case MB::Saber::eState::End:
			break;
		case MB::Saber::eState::Sit:
			Sit();
			break;
		case MB::Saber::eState::SItAttack:
			SitAttack();
			break;
		case MB::Saber::eState::StandToSit:
			StandToSit();
			break;
		default:
			break;
		}

	}
	void Saber::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}



	void Saber::Idle()
	{
		Animator* animator = GetComponent<Animator>();
		mSaberDownMove = false;

		mDoubleJumpCheck = false;

		mCollider->SetSize(Vector2(-200.0f, 400.0f));
		mCollider->SetOffset(Vector2(0.0f, 25.0f));

		

		Transform* tr = GetComponent<Transform>();

		if (Input::GetKeyDown(eKeyCode::W))
		{
			animator->PlayAnimation(L"Saber_JumpToUp", false);
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);

			mState = eState::JumpToUp;
		}

		if (Input::GetKey(eKeyCode::D))
		{


			animator->PlayAnimation(L"Saber_FrontMove", true);
			mState = eState::Move;
			mSaberFrontMove = true;

			animator->PlayAnimation(L"Saber_FrontMove", true);
			mState = eState::Move;

		}
		if (Input::GetKey(eKeyCode::S))
		{
			animator->PlayAnimation(L"Saber_Sit", true);
			mState = eState::Sit;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			animator->PlayAnimation(L"Saber_BackMove", true);
			mState = eState::Move;

			mSaberBackMove = true;

		}

		if (Input::GetKey(eKeyCode::H))
		{
			Transform* tr = GetComponent<Transform>();

			mHitbox->SetSize(Vector2(-100.0f, 50.0f));
			mHitbox->SetOffset(Vector2(100.0f, -20.0f));

			animator->PlayAnimation(L"Saber_AAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKey(eKeyCode::J))
		{

			Transform* tr = GetComponent<Transform>();

			mHitbox->SetSize(Vector2(-200.0f, 100.0f));
			mHitbox->SetOffset(Vector2(100.0f, 0.0f));

			animator->PlayAnimation(L"Saber_BAttack", false);
			mState = eState::Attack;
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			mHitbox->SetSize(Vector2(-150.0f, 400.0f));
			mHitbox->SetOffset(Vector2(170.0f, 0.0f));

			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Saber_CAttack", false);
			mState = eState::Attack;
		}


		if (Input::GetKey(eKeyCode::H) && mSaberDownMove == true && mSaberFrontMove == true)
		{
			Transform* tr = GetComponent<Transform>();
		}


	}
	void Saber::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		AttackFunc();
		


		if (Input::GetKeyDown(eKeyCode::W))
		{
			animator->PlayAnimation(L"Saber_JumpToUp", false);
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);

			mState = eState::JumpToUp;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::S))
		{
			//if (pos.y < 480.0f)
			//pos.y += 300.0f * Time::DeltaTime();

			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 300.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}
		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::W)
			|| Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::D))
		{
			Animator* animator = GetComponent<Animator>();
			animator->PlayAnimation(L"Saber_Idle", true);
			mState = eState::Idle;
		}


		if (Input::GetKey(eKeyCode::H))
		{
			mHitbox->SetSize(Vector2(-100.0f, 50.0f));
			mHitbox->SetOffset(Vector2(100.0f, -20.0f));

			animator->PlayAnimation(L"Saber_AAttack", false);
			mState = eState::Attack;

		}

		if (Input::GetKey(eKeyCode::J))
		{
			mHitbox->SetSize(Vector2(-200.0f, 100.0f));
			mHitbox->SetOffset(Vector2(100.0f, 0.0f));

			animator->PlayAnimation(L"Saber_BAttack", false);
			mState = eState::Attack;
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			mHitbox->SetSize(Vector2(-150.0f, 400.0f));
			mHitbox->SetOffset(Vector2(170.0f, 0.0f));

			animator->PlayAnimation(L"Saber_CAttack", false);
			mState = eState::Attack;
		}

	}
	void Saber::BackMove()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 velocity = mRigidbody->GetVelocity();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		mSaberBackMove = true;

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKeyDown(eKeyCode::H) || Input::GetKeyDown(eKeyCode::J) || Input::GetKeyDown(eKeyCode::U))
		{
			mCurState = eState::Attack;
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			mAnimator->PlayAnimation(L"Saber_Idle", true);
			mState = eState::Idle;
		}

		if (Input::GetKey(eKeyCode::H))
		{
			mHitbox->SetSize(Vector2(-100.0f, 50.0f));
			mHitbox->SetOffset(Vector2(100.0f, -20.0f));

			animator->PlayAnimation(L"Saber_AAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKey(eKeyCode::J))
		{
			mHitbox->SetSize(Vector2(-200.0f, 100.0f));
			mHitbox->SetOffset(Vector2(100.0f, 0.0f));

			animator->PlayAnimation(L"Saber_BAttack", false);
			mState = eState::Attack;
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			mHitbox->SetSize(Vector2(-150.0f, 400.0f));
			mHitbox->SetOffset(Vector2(170.0f, 0.0f));

			animator->PlayAnimation(L"Saber_CAttack", false);
			mState = eState::Attack;
		}
	}
	void Saber::Attack()
	{
		Animator* animator = GetComponent<Animator>();
		if (mSaberDownMove == true)
		{
			if (animator->IsActiveAnimationComplete())
			{
				mHitbox->SetSize(Vector2(0.0f, 0.0f));
				mHitbox->SetOffset(Vector2(0.0f, 0.0f));

				animator->PlayAnimation(L"Saber_Sit", true);
				mState = eState::Sit;
			}
		}
		if (mSaberDownMove == false)
		{
			if (animator->IsActiveAnimationComplete())
			{
				mHitbox->SetSize(Vector2(0.0f, 0.0f));
				mHitbox->SetOffset(Vector2(0.0f, 0.0f));

				animator->PlayAnimation(L"Saber_Idle", true);
				mState = eState::Idle;
			}

		}

	}
	void Saber::Jump_Attack()
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
				animator->PlayAnimation(L"Saber_JumpToDown", true);
			}


			if (rb->GetGround() == true)
			{
				animator->PlayAnimation(L"Saber_Idle", true);
				mState = eState::Idle;

			}
			/*animator->PlayAnimation(L"PlayerIdle", true);
			mState = eState::Idle;*/
			if (animator->IsActiveAnimationComplete())
			{


				animator->PlayAnimation(L"Saber_JumpToDown", true);
				mState = eState::JumpToFall;
				mDoubleJumpCheck = false;
			}
		}
	}
	void Saber::Hit()
	{

	}
	void Saber::JumpToUp()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyDown(eKeyCode::W) && mDoubleJumpCheck == false)
		{
			animator->PlayAnimation(L"Saber_JumpToUp", false);
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);

			mDoubleJumpCheck = true;
			mState = eState::JumpToFall;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::S))
		{

			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::H))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Saber_JumpAAttack", false);
			mState = eState::Jump_Attack;
		}

		if (Input::GetKey(eKeyCode::J))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Saber_JumpBAttack", false);
			mState = eState::Jump_Attack;
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Saber_JumpCAttack", false);
			mState = eState::Jump_Attack;
		}

		if (animator->IsActiveAnimationComplete())
		{
			mHitbox->SetSize(Vector2(0.0f, 0.0f));
			mHitbox->SetOffset(Vector2(0.0f, 0.0f));

			animator->PlayAnimation(L"Saber_JumpToDown", true);
			mState = eState::JumpToFall;
		}
	}
	void Saber::JumpToFall()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();

		if (rb->GetGround() != false)
		{
			animator->PlayAnimation(L"Saber_JumpToDown", true);

		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			//GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 300.0f * Time::DeltaTime();

		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 300.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::S))
		{
			//if (pos.y < 480.0f)
			//pos.y += 300.0f * Time::DeltaTime();

			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 300.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}

		if (Input::GetKey(eKeyCode::H))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Saber_JumpAAttack", false);
			mState = eState::Jump_Attack;

		}

		if (Input::GetKey(eKeyCode::J))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Saber_JumpBAttack", false);
			mState = eState::Jump_Attack;
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Saber_JumpCAttack", false);
			mState = eState::Jump_Attack;
		}

		if (rb->GetGround() == true)
		{
			animator->PlayAnimation(L"Saber_Idle", true);
			mState = eState::Idle;
		}
	}
	void Saber::Double_Jump()
	{
	}
	void Saber::Sit()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		mSaberDownMove = true;

		mCollider->SetSize(Vector2(-200.0f, 300.0f));
		mCollider->SetOffset(Vector2(0.0f, 73.0f));


		if (Input::GetKey(eKeyCode::H))
		{
			Transform* tr = GetComponent<Transform>();


			animator->PlayAnimation(L"Saber_SitAAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKey(eKeyCode::J))
		{
			Transform* tr = GetComponent<Transform>();

			animator->PlayAnimation(L"Saber_SitBAttack", false);
			mState = eState::Attack;
		}
		if (Input::GetKey(eKeyCode::Y))
		{
			Transform* tr = GetComponent<Transform>();


			animator->PlayAnimation(L"Saber_SitCAttack", false);
			mState = eState::Attack;
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			Animator* animator = GetComponent<Animator>();
			animator->PlayAnimation(L"Saber_Idle", true);
			mState = eState::Idle;
		}

	}
	void Saber::SitAttack()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"Saber_Idle", true);
			mState = eState::Idle;
		}
	}
	void Saber::StandToSit()
	{
	}

	void Saber::AttackFunc()
	{
	}

	void Saber::OnCollisionEnter(Collider* other)
	{
		Shiki* shiki = dynamic_cast<Shiki*>(other->GetOwner());
		if (shiki == nullptr)
			return;
		Transform* Str = shiki->GetComponent<Transform>();
		Vector2 pos = Str->GetPosition();

		Animator* Shiki_Hit = shiki->GetComponent<Animator>();
		Shiki_Hit->PlayAnimation(L"Shiki_StandHit");
	}
	void Saber::OnCollisionStay(Collider* other)
	{
	}
	void Saber::OnCollisionExit(Collider* other)
	{
	}
}