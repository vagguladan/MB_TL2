#include "MBFloor.h"
#include "MBSaber.h"
#include "MBCollider.h"
#include "MBRigidBody.h"
#include "MBTransform.h"
#include "MBShiki.h"

namespace MB
{
	Floor::Floor()
	{
	}
	Floor::~Floor()
	{
	}
	void Floor::Initialize()
	{
	}
	void Floor::Update()
	{
		GameObject::Update();
	}
	void Floor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Floor::OnCollisionEnter(Collider* other)
	{
		Saber* saber = dynamic_cast<Saber*>(other->GetOwner());
		Shiki* shiki= dynamic_cast<Shiki*>(other->GetOwner());

		Transform* tr = nullptr;
		Rigidbody* rb = nullptr;

		if (saber != nullptr)
		{
			Transform* tr = saber->GetComponent<Transform>();
			Rigidbody* rb = saber->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.y -= (scale - len) - 1.0f;
				tr->SetPosition(playerPos);
			}

			rb->SetGround(true);
		}

		if (shiki != nullptr)
		{
			Transform* tr = shiki->GetComponent<Transform>();
			Rigidbody* rb = shiki->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (len < scale)
			{
				Vector2 ShikiPos = tr->GetPosition();
				ShikiPos.y -= (scale - len) - 1.0f;
				tr->SetPosition(ShikiPos);
			}

			rb->SetGround(true);
		}
	}
	void Floor::OnCollisionStay(Collider* other)
	{
	}
	void Floor::OnCollisionExit(Collider* other)
	{

	}
}