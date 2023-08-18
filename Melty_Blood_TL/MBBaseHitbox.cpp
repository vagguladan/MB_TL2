#include "MBBaseHitbox.h"
#include "MBTransform.h"
#include "MBTime.h"
#include "MBSaber.h"
#include "MBGameObject.h"
#include "MBCollider.h"
#include "MBCollisionManager.h"
#include "MBObject.h"

namespace MB
{
	HitBox::HitBox()
		: mSaber(nullptr)
		, mTime(0.f)
	{
	}
	HitBox::~HitBox()
	{
	}
	void HitBox::Initialize()
	{
		mCollider = AddComponent<Collider>();
	}
	void HitBox::Update()
	{
		GameObject::Update();
		mTime -= Time::DeltaTime();
		if (mTime < 0.1f)
		{
			Destroy(this);
		}
	}
	void HitBox::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HitBox::OnCollisionEnter(Collider* other)
	{
	}
	void HitBox::OnCollisionStay(Collider* other)
	{
	}
	void HitBox::OnCollisionExit(Collider* other)
	{
	}
	void HitBox::SlashCollider()
	{
		mCollider->SetNotColColor(RGB(50, 50, 255));
	}
}