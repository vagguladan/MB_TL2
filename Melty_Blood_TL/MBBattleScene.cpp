#include "MBBattleScene.h"
#include "MBSaber.h"
#include "MBSpriteRender.h"
#include "MBObject.h"
#include "MBInput.h"
#include "MBTexture.h"
#include "MBTransform.h"
#include "MBResources.h"
#include "MBCamera.h"
#include "MBAnimator.h"
#include "MBBackGround.h"
#include "MBFloor.h"
#include "MBRigidBody.h"
#include "MBCollider.h"
#include "MBCollisionManager.h"
#include "MBGameObject.h"
#include "MBPlayer.h"
#include "MBShiki.h"
#include "MBWall.h"



namespace MB
{
	BattleScene1::BattleScene1()
	{
	}
	BattleScene1::~BattleScene1()
	{
	}
	void BattleScene1::Initialize()
	{
		//배경화면
		Texture* BGimage = Resources::Load<Texture>(L"BattleBackGroundImgae"
			, L"..\\Resources\\Image\\BackGround\\Lessons_CS_Screenshot_01.png");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(BGimage);
		bgsr->SetScale(Vector2(2.0f, 1.8f));
		bgsr->SetAffectCamera(false);
		bg->GetComponent<Transform>()->SetPosition(Vector2(640.0f, 360.0f));


		//플레이어블.

		Saber* saber = object::Instantiate<Saber>(eLayerType::Player);
		Transform* tr2 = saber->GetComponent<Transform>();
		tr2->SetPosition(Vector2(640.0f, 360.0f));
		saber->GetComponent<Animator>()->SetAffectedCamera(true);

		//시키 

		Shiki* shiki = object::Instantiate<Shiki>(eLayerType::Enemy);
		Transform* tr3 = shiki->GetComponent<Transform>();
		tr3->SetPosition(Vector2(1200.0f, 360.0f));
		shiki->GetComponent<Animator>()->SetAffectedCamera(true);


		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* col = floor->AddComponent<Collider>();
		col->SetSize(Vector2(2000.0f, 100.0f));
		tr2 = floor->GetComponent<Transform>();

		tr2->SetPosition(Vector2(640.0f, 700.0f));

		//Wall* wall_L = object::Instantiate<Wall>(eLayerType::Wall);
		//Collider* col_WL = wall_L->AddComponent<Collider>();
		//Transform* Tr_WL = wall_L->GetComponent<Transform>();
		//

		//col_WL->SetSize(Vector2(100.0f, 2000.0f));
		//Tr_WL->SetPosition(Vector2(100.0f, 0.0f));

		

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Floor, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
		Camera::SetTarget(saber);
	}
	void BattleScene1::Update()
	{
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
		if (Input::GetKeyUp(eKeyCode::N))
		{
			Camera::SetTarget(nullptr);
			Camera::Initialize();
			SceneManager::LoadScene(L"TitleScene");
		}

		Scene::Update();
	}
	void BattleScene1::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}