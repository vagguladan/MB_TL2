#include "MBWall.h"
#include "MBSaber.h"
#include "MBCollider.h"
#include "MBRigidBody.h"
#include "MBTransform.h"
#include "MBShiki.h"

namespace MB
{
	Wall::Wall()
	{
	}
	Wall::~Wall()
	{
	}
	void Wall::Initialize()
	{
	}
	void Wall::Update()
	{
		GameObject::Update();
	}
	void Wall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Wall::OnCollisionEnter(Collider* other)
	{
		Saber* saber = dynamic_cast<Saber*>(other->GetOwner());
		Shiki* shiki = dynamic_cast<Shiki*>(other->GetOwner());

		Transform* tr = nullptr;
		Rigidbody* rb = nullptr;

		if(saber!=nullptr)
		{
			Transform* tr = saber->GetComponent<Transform>();
			Rigidbody* rb = saber->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.x -= (scale - len) - 1.0f;
				tr->SetPosition(playerPos);
			}
		
			rb->SetWall(true);
		}

	}
	void Wall::OnCollisionStay(Collider* other)
	{
	}
	void Wall::OnCollisionExit(Collider* other)
	{
	}
}