#pragma once
#include "MBScene.h"

namespace MB
{
	class BattleScene1 : public Scene
	{
	public:
		BattleScene1();
		virtual ~BattleScene1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}