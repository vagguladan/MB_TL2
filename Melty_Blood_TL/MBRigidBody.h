#pragma once
#include "MBComponent.h"

namespace MB
{
	using namespace math;
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddForce(Vector2 force) { mForce += force; }
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() { return mbGround; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }

		void SetWall(bool wall) { mbWall = wall; }
		bool GetWall() { return mbWall; }

	private:
		float mMass;

		float mFriction;
		float mStaticFriction;
		float mKineticFrction;
		float mCoefficentFrction;

		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mGravity;
		Vector2 mLimitedVelocity;

		bool mbGround;
		bool mbWall;

	};
}