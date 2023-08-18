#include "MBTransform.h"
#include "MBInput.h"
#include "MBTime.h"

namespace MB
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mRotation(0.0f)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::Render(HDC hdc)
	{
	}
}