#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGameObject.h"
#include "UiTextGameObject.h"
#include "Test.h"

void SceneDev1::Init()
{
	GameObject* obj = AddGameObject(new SpriteGameObject("player"));


	obj->SetOrigin(Origins::MiddleCenter);
	obj->SetPosition({ 1920.f * 0.5f, 1080 * 0.5f });
	obj->CreateCollider(ColliderType::Circle);

	obj = AddGameObject(new UITextGameObject("fonts/KOMIKAP_.ttf", "", 100));
	obj->SetOrigin(Origins::TopLeft);
	obj->SetPosition({ });
	((UITextGameObject*)obj)->SetString("SceneDev1");

	Test* test = AddGameObject(new Test("player"));
	test->CreateCollider(ColliderType::Rectangle);


	Scene::Init();
}

void SceneDev1::Enter()
{
	TEXTURE_MANAGER.Load("player", "graphics/player.png");


	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");
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
