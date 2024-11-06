#pragma once
#include "Scene.h"

class SceneDev1 : public Scene
{
private:
	GameObject* test;

public:
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Release() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window)override;
public:
	SceneDev1();
	~SceneDev1();

};

