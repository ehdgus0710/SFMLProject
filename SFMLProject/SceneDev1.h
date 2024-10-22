#pragma once
#include "Scene.h"

class SceneDev1 : public Scene
{
public:
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Release() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow& window)override;
public:
	SceneDev1();
	~SceneDev1();

};

