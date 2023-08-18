#include "MBBackGround.h"
#include "MBTransform.h"
#include "MBTime.h"
#include "MBInput.h"
#include "MBSpriteRender.h"

namespace MB
{
	BackGround::BackGround()
	{
	}
	BackGround::~BackGround()
	{
	}
	void BackGround::Initialize()
	{
	}
	void BackGround::Update()
	{
		GameObject::Update();
	}
	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}