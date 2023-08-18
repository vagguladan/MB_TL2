#pragma once
#include "MBEntity.h"

namespace MB
{
	using namespace enums;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);


		void SetOwner(class GameObject* Owner) { mOwner = Owner; }
		class GameObject* GetOwner() { return mOwner; }

	private:
		const eComponentType mType;
		class GameObject* mOwner;
	};
}
