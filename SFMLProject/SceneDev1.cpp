#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGameObject.h"
#include "UiTextGameObject.h"
#include "Test.h"

#include "Animation.h"
#include "Animator.h"

void SceneDev1::Init()
{
	Scene::Init();
}

void SceneDev1::Enter()
{
	TEXTURE_MANAGER.Load("Char", "graphics/CharRun.png");

	TEXTURE_MANAGER.Load("PlayerMove", "graphics/PC_Move.png");
	TEXTURE_MANAGER.Load("PlayerDash", "graphics/PC_Dash.png");

	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");


	/*GameObject* obj = AddGameObject(new SpriteGameObject("player"), RenderLayer::Default);

	obj->SetOrigin(Origins::MiddleCenter);
	obj->SetPosition({ 1920.f * 0.5f, 1080 * 0.5f });
	obj->CreateCollider(ColliderType::Circle, ColliderLayer::Default);

	obj = AddGameObject(new UITextGameObject("fonts/KOMIKAP_.ttf", "", 100), RenderLayer::Default);
	obj->SetOrigin(Origins::TopLeft);
	obj->SetPosition({ });
	((UITextGameObject*)obj)->SetString("SceneDev1");*/

	Test* test = AddGameObject(new Test("PlayerMove"), RenderLayer::Default);
	// test->CreateCollider(ColliderType::Rectangle, ColliderLayer::Default);

	test->SetOrigin(Origins::MiddleCenter);
	test->Awake();
	test->CreateAnimator();
	test->animator->CreateAnimation("PlayerMove", "PlayerMove", { 128,128 }, 8, 0.1f, true);
	test->animator->CreateAnimation("PlayerDash", "PlayerDash", { 256,128 }, 8, 0.1f, true);
	test->animator->ChangeAnimation("PlayerDash", true);

	test->SetPosition({ 1920.f * 0.5f, 1080 * 0.5f });

	test->animator->Start();
	//Test* test2 = AddGameObject(new Test("Char"), RenderLayer::Default);
	//// test->CreateCollider(ColliderType::Rectangle, ColliderLayer::Default);

	//test2->SetOrigin(Origins::MiddleCenter);
	//test2->Awake();
	//test2->CreateAnimator();
	//test2->animator->CreateAnimation("Char", "CharRun", { 32,32 }, 8, 0.1f, true);
	//test2->animator->ChangeAnimation("CharRun", true);
	//test2->SetPosition({ 1920.f * 0.5f + 32.f, 1080 * 0.5f });

	Scene::Enter();
}

void SceneDev1::Exit()
{
	TEXTURE_MANAGER.unLoad("player");
	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");
	Scene::Exit();
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
