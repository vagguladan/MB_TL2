#include "MBCharcterScene.h"
#include "MBApplication.h"
#include "MBSpriteRender.h"
#include "MBObject.h"
#include "MBInput.h"
#include "MBTexture.h"
#include "MBTransform.h"
#include "MBResources.h"
#include "MBBackGround.h"
#include "MBAnimator.h"
#include "MBCamera.h"

namespace MB
{
	CharcterScene::CharcterScene()
	{
	}
	CharcterScene::~CharcterScene()
	{
	}
	void CharcterScene::Initialize()
	{
		Texture* image = Resources::Load<Texture>(L"CharterSelectImgae"
			, L"..\\Resources\\Image\\CharcterScene\\20230804164430_2.png");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(0.6f, 0.7f));
		bgsr->SetAffectCamera(false);

		bg->GetComponent<Transform>()->SetPosition(Vector2(650.0f, 380.0f));
	}
	void CharcterScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::C))
		{
			SceneManager::LoadScene(L"CharaterScene");
		}
		if (Input::GetKeyDown(eKeyCode::T))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
		if (Input::GetKeyDown(eKeyCode::B))
		{
			SceneManager::LoadScene(L"BattleScene");
		}
	}
	void CharcterScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}