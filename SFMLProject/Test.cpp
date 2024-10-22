#include "stdafx.h"
#include "Test.h"


Test::Test(const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
{
}

void Test::Update(const float& deltaTime)
{
	position = sf::Vector2f(InputManager::GetInstance().GetMousePosition());
	SetPosition(position);
	SpriteGameObject::Update(deltaTime);
}


Test::~Test()
{
}
