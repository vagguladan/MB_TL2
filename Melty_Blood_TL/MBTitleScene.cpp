#include "MBTitleScene.h"
#include "MBSpriteRender.h"
#include "MBObject.h"
#include "MBTexture.h"
#include "MBResources.h"
#include "MBBackGround.h"
#include "MBInput.h"
#include "MBCamera.h"
#include "MBTransform.h"


namespace MB
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Texture* image = Resources::Load<Texture>(L"TitleBackGroundImgae"
			, L"..\\Resources\\Image\\Tiltle\\20230804204526_1.png");


		BackGround* bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(0.6f, 0.7f));
		bgsr->SetAffectCamera(false);

		bg->GetComponent<Transform>()->SetPosition(Vector2(650.0f, 380.0f));
	}
	void TitleScene::Update()
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
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}