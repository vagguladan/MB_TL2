#include "MBCollider.h"
#include "MBTransform.h"
#include "MBGameObject.h"
#include "MBCamera.h"

namespace MB
{
	UINT Collider::mCollisionCount = 0;
	Collider::Collider()
		: Component(eComponentType::Collider)
		, mSize(Vector2::Zero)
		, mOffset(Vector2::Zero)
		, mCollisionNumber(-1)
		, mbIsCollision(false)
		, mOnColColor(RGB(255, 50, 50))
		, mNotColColor(RGB(50, 255, 50))
	{
		mCollisionNumber = mCollisionCount;
		mCollisionCount++;
	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
	}
	void Collider::Update()
	{
	}
	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPosition = pos + mOffset;

		pos.x -= mSize.x / 2.0f;
		pos.y -= mSize.y / 2.0f;
		pos.x += mOffset.x;
		pos.y += mOffset.y;

		pos = Camera::CalculatePosition(pos);

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN pen = NULL;
		if (mbIsCollision)
		{
			pen = CreatePen(PS_SOLID, 2, mOnColColor);
		}
		else
		{
			pen = CreatePen(PS_SOLID, 2, mNotColColor);
		}

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc
			, pos.x, pos.y
			, pos.x + mSize.x, pos.y + mSize.y);

		SelectObject(hdc, oldBrush);
		DeleteObject(transparentBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);

	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(other);
	}
}