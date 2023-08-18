#pragma once
#include "MBGameObject.h"

namespace MB
{
	class Wall : public GameObject
	{
	public:
		Wall();
		virtual ~Wall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	};
}