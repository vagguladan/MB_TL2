#include "MBSaberHitBox.h"
#include "MBTransform.h"
#include "MBSaber.h"
#include "MBCollider.h"
#include "MBTime.h"
#include "MBInput.h"
#include "MBAnimator.h"
#include "MBObject.h"
#include "MBGameObject.h"

#include "MBCollisionManager.h"
#include "MBShiki.h"



namespace MB
{
	SaberHitBox::SaberHitBox()
		: mSaber(nullptr)
	{
	}
	SaberHitBox::~SaberHitBox()
	{
	}
	void SaberHitBox::Initialize()
	{
	}
	void SaberHitBox::Update()
	{
		GameObject::Update();

		mTime -= Time::DeltaTime();
		if (mTime < 0.1f)
		{
			Destroy(this);
		}
	}
	void SaberHitBox::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
	void SaberHitBox::MakeAnimation()
	{
	}
	void SaberHitBox::OnCollisionEnter(Collider* _other)
	{
		Shiki* shiki = dynamic_cast<Shiki*>(_other->GetOwner());
		if (shiki == nullptr) 
			return;
		Transform* Str = shiki->GetComponent<Transform>();
		Vector2 pos = Str->GetPosition();

		Animator* Shiki_Hit = shiki->GetComponent<Animator>();
		Shiki_Hit -> PlayAnimation(L"Shiki_StandHit");

	}
	void SaberHitBox::OnCollisionStay(Collider* _other)
	{
	}
	void SaberHitBox::OnCollisionExit(Collider* _other)
	{
	}
}