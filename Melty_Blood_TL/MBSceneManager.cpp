#include "MBSceneManager.h"
#include "MBTitleScene.h"
#include "MBCharcterScene.h"
#include "MBBattleScene.h"


namespace MB
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<CharcterScene>(L"CharaterScene");
		CreateScene<BattleScene1>(L"BattleScene");
		LoadScene(L"TitleScene");
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}
	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;
		return iter->second;
	}
}