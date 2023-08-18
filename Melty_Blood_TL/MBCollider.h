#pragma once
#include "MBComponent.h"

namespace MB
{
	using namespace math;
	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetOffset() { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetPosition() { return mPosition; }
		UINT GetCollisionNumber() { return mCollisionNumber; }

		void SetOnColColor(COLORREF color) { mOnColColor = color; }

		__forceinline void SetLineColor(COLORREF _color) { lineColor = _color; }
		__forceinline void SetCollisionLineColor(COLORREF _color) { collisionLineColor = _color; }

		__forceinline void SetActive(BOOL _active) { mbActive = _active; }

		void SetNotColColor(COLORREF color) { mNotColColor = color; }

	private:
		static UINT mCollisionCount;

		Vector2 mSize;
		Vector2 mOffset;
		Vector2 mPosition;

		COLORREF mOnColColor;
		COLORREF mNotColColor;


		COLORREF lineColor;
		COLORREF collisionLineColor;
		COLORREF inActiveLineColor;

		UINT mCollisionNumber;
		bool mbIsCollision;

		BOOL mbActive;
	};
}