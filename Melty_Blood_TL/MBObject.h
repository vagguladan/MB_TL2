#pragma once
#include "MBScene.h"
#include "MBGameObject.h"
#include "MBSceneManager.h"
#include "MBTransform.h"

namespace MB::object
{
	template<typename T>
	static __forceinline T* Instantiate(eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		gameObject->Initialize();

		return gameObject;
	}

	template <typename T>
	static __forceinline T* Instantiate(eLayerType type, Vector2 position)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		gameObject->Initialize();
		gameObject->GetComponent<Transform>()->SetPosition(position);

		return gameObject;
	}
}