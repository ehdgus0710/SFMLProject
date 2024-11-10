#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGameObject.h"
#include "UiTextGameObject.h"
#include "Test.h"

#include "Animation.h"
#include "Animator.h"

#include "Camera.h"
#include "CameraManger.h"

#include "TestPlayer.h"
#include "TileMap.h"

void SceneDev1::Init()
{
	Scene::Init();
}

void SceneDev1::Enter()
{
	CameraManger::GetInstance().SetCamera(mainCamera);
	CameraManger::GetInstance().SetCamera(uICamera);

	TEXTURE_MANAGER.Load("Background", "graphics/Background_Cave_mix.png");
	TEXTURE_MANAGER.Load("Char", "graphics/CharRun.png");
	TEXTURE_MANAGER.Load("Player", "graphics/player.png");
	TEXTURE_MANAGER.Load("PlayerMove", "graphics/PC_Move.png");
	TEXTURE_MANAGER.Load("PlayerDash", "graphics/PC_Dash.png");
	TEXTURE_MANAGER.Load("background", "graphics/background_sheet.png");

	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");

	TestPlayer* testPlayer = AddGameObject(new TestPlayer("Player", "Player"),LayerType::Player);
	testPlayer->Awake();
	mainCamera->SetFollowTarget(testPlayer, true);
	mainCamera->SetCameraLimitRect({ -2000.f, 2000.f, -2000.f, 2000.f });

	SpriteGameObject* background = AddGameObject(new SpriteGameObject("Background", "Background"), LayerType::Default);

	GameObject* obj = AddGameObject(new Test("Player"), LayerType::Default);
	obj->SetOrigin(Origins::MiddleCenter);
	obj->SetPosition({ 1920.f * 0.5f, 1080 * 0.5f });
	obj->CreateCollider(ColliderType::Rectangle, ColliderLayer::Default);



	TileMap* tileMap = AddGameObject(new TileMap("background", "TileMap"), LayerType::Default);
	tileMap->SetTileInfo("background", { 50,50 }, { 64.f, 64.f }, { 50,50 });

	//test = obj;
	//mainCamera->SetFollowTarget(test);

	//obj = AddGameObject(new SpriteGameObject("Player"), LayerType::UI);
	//obj->SetOrigin(Origins::MiddleCenter);
	//obj->SetPosition({ 1920.f * 0.5f + 300.f, 1080 * 0.5f });
	//obj->CreateCollider(ColliderType::Rectangle, ColliderLayer::Default);
	//

	///*obj = AddGameObject(new UITextGameObject("fonts/KOMIKAP_.ttf", "", 100), RenderLayer::Default);
	//obj->SetOrigin(Origins::TopLeft);
	//obj->SetPosition({ });
	//((UITextGameObject*)obj)->SetString("SceneDev1");*/

	//Test* test = AddGameObject(new Test("PlayerMove"), LayerType::Default);
	////test->CreateCollider(ColliderType::Rectangle, ColliderLayer::Default);

	//test->SetOrigin(Origins::MiddleCenter);
	//test->Awake();
	//test->CreateAnimator();
	//test->animator->CreateAnimation("PlayerMove", "PlayerMove", { 128,128 }, 8, 0.1f, true);
	//test->animator->CreateAnimation("PlayerDash", "PlayerDash", { 256,128 }, 8, 0.1f, true);
	//test->animator->ChangeAnimation("PlayerDash", true);

	//test->SetPosition({ 1920.f * 0.5f, 1080 * 0.5f });

	//test->animator->Start();

	//Test* test2 = AddGameObject(new Test("Char"), LayerType::Default);
	//test2->CreateCollider(ColliderType::Rectangle, ColliderLayer::Default);

	//test2->SetOrigin(Origins::MiddleCenter);
	//test2->Awake();
	//test2->CreateAnimator();
	//test2->animator->CreateAnimation("Char", "CharRun", { 32,32 }, 8, 0.1f, true);
	//test2->animator->ChangeAnimation("CharRun", true);
	//test2->SetPosition({ 1920.f * 0.5f + 32.f, 1080 * 0.5f });

	//cameraPosition = mainCamera->GetCameraPosition();

	ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Default, ColliderLayer::Default);

	Scene::Enter();
}

void SceneDev1::Exit()
{
	TEXTURE_MANAGER.unLoad("player");
	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");
	Scene::Exit();

	CameraManger::GetInstance().Clear();
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	/*if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Space))
		SCENE_MANAGER.ChangeScene(SceneIds::SceneDev2);*/

	/*if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		cameraPosition += sf::Vector2f::left * cameraSpeed * dt;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		cameraPosition += sf::Vector2f::right * cameraSpeed * dt;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Up))
	{
		cameraPosition += sf::Vector2f::up * cameraSpeed * dt;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Down))
	{
		cameraPosition += sf::Vector2f::down * cameraSpeed * dt;
	}

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Z))
	{
		test->SetRotation(test->GetRotation() + 10.f * dt);
	}

	test->SetPosition((sf::Vector2f)InputManager::GetInstance().GetMousePosition());

	mainCamera->SetCameraPosition(cameraPosition);*/
}

void SceneDev1::Render(sf::RenderWindow& window)
{
	Scene::Render(window);
}

SceneDev1::SceneDev1()
	: Scene(SceneIds::SceneDev1)
{

}

SceneDev1::~SceneDev1()
{
}
