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

#include "Player.h"

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

	TEXTURE_MANAGER.Load("enemies", "graphics/enemies.png");
	TEXTURE_MANAGER.Load("background", "graphics/background_sheet.png");
	TEXTURE_MANAGER.Load("mario_bros", "graphics/mario_bros.png");
	TEXTURE_MANAGER.Load("tiles", "graphics/tiles.png");
	TEXTURE_MANAGER.Load("characters", "graphics/characters.gif");

	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");
	ResourcesManager<Animation>::GetInstance().Load("marioIdle", "animations/marioIdle.csv");

	Player* testPlayer = AddGameObject(new Player("Player"),LayerType::Player);
	testPlayer->Awake();
	testPlayer->CreateAnimator();

	auto animator = testPlayer->GetAnimator();
	animator->AddAnimation(&ResourcesManager<Animation>::GetInstance().Get("marioIdle"), "marioIdle");
	mainCamera->SetFollowTarget(testPlayer, true);
	// mainCamera->SetCameraLimitRect({ -2000.f, 2000.f, -2000.f, 2000.f });

	TileMap* tile = AddGameObject(new TileMap("tiles", "Map"), LayerType::Default);
	tile->SetTileInfo("tiles", { 30,30 }, { 64.f,64.f }, { 32,32 });
	tile->SaveCsv("TileMap/test.csv");
	tile->LoadCsv("TileMap/test.csv");
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
