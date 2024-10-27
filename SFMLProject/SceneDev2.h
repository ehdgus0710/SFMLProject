#pragma once
#include "Scene.h"

class SceneDev2 : public Scene
{
public:
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Release() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow& window)override;
public:
	SceneDev2();
	~SceneDev2();
};

