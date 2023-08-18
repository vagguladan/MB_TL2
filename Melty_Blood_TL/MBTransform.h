#pragma once
#include "MBComponent.h"

namespace MB
{
	using namespace math;
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetPosition(Vector2 pos) { mPosition = pos; }
		Vector2 GetPosition() { return mPosition; }
		float GetRotation() { return mRotation; }
		
	private:
		Vector2 mPosition;
		float mRotation;
	};
}