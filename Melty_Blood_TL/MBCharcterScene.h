#pragma once
#include "MBScene.h"

namespace MB
{
	class CharcterScene : public Scene
	{
	public:
		CharcterScene();
		virtual ~CharcterScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	};
}