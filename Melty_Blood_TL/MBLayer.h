#pragma once
#include "MBEntity.h"
#include "MBGameObject.h"

namespace MB
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* GameObject)
		{
			mGameObjects.push_back(GameObject);

		}

		std::vector<GameObject*>& GetGameObject() { return mGameObjects;}

	private:
		std::vector<GameObject*> mGameObjects;
	};
}