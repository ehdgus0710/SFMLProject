#include "stdafx.h"
#include "Test.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"

Test::Test(const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
	, animator(nullptr)
{
}

void Test::SetPosition(const sf::Vector2f& pos)
{
	SpriteGameObject::SetPosition(pos);
	if(animator != nullptr)
		animator->GetCurrentSprite().setPosition(pos);
}

void Test::SetSpriteRect()
{
	//sprite.setTextureRect(animation->frameInfoVector[animation->currentIndex].uvRect);
}

void Test::Awake()
{
	SpriteGameObject::Awake();
}

void Test::Start()
{
	SpriteGameObject::Start();
	//animation->SetTest(this);
	SetSpriteRect();
}

void Test::Update(const float& deltaTime)
{
	/*position = sf::Vector2f(InputManager::GetInstance().GetMousePosition());
	SetPosition(position);
	SpriteGameObject::Update(deltaTime);*/

	if (animator != nullptr)
		animator->Update(deltaTime);
}

void Test::Render(sf::RenderWindow& renderWindow)
{
	if (collider != nullptr)
		collider->Render(renderWindow);

	if(animator != nullptr)
		animator->Render(renderWindow);
	else
		SpriteGameObject::Render(renderWindow);
}

void Test::CreateAnimator()
{
	if (animator != nullptr)
		return;

	animator = new Animator();
}


Test::~Test()
{
	if(animator != nullptr)
		delete animator;
}
