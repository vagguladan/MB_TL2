#pragma once
#include "CommonInclude.h"
#include "MBGameObject.h"

namespace MB
{
	using namespace math;
	class Camera
	{
	public:

		static void Initialize();
		static void Update();

		static Vector2 CalculatePosition(Vector2 pos) { return pos - mDistance; }
		static  GameObject* GetTarget() {return mTarget;}
		static void SetTarget(GameObject* target) { mTarget = target; }

		void SetLookPos(Vector2 look) { mLookPosition = look; }

	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;

		static GameObject* mTarget;
	};
}