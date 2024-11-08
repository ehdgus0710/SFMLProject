#include "stdafx.h"
#include "TestPlayer.h"

TestPlayer::TestPlayer(const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
	, rigidBody(nullptr)
	, speed(500.f)
	, isJump(false)
{
}

TestPlayer::~TestPlayer()
{
	if (rigidBody != nullptr)
		delete rigidBody;
}

void TestPlayer::InputMove()
{
	moveDirection = sf::Vector2f::zero;

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		moveDirection.x += -1.f;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		moveDirection.x += 1.f;
	}
	if(rigidBody != nullptr)
		rigidBody->SetVelocity({ moveDirection.x * speed , rigidBody->GetCurrentVelocity().y});
}

void TestPlayer::InputJump()
{
	if (isJump)
		return;


	isJump = true;
	rigidBody->SetGround(false);
	rigidBody->SetVelocity({ rigidBody->GetCurrentVelocity().x, -500.f});
}

void TestPlayer::Awake()
{
	rigidBody = new Rigidbody(this);

	rigidBody->SetGround(true);
}

void TestPlayer::Update(const float& deltaTime)
{


	InputMove();


	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Space))
		InputJump();
}

void TestPlayer::FixedUpdate(const float& deltaTime)
{
	if(rigidBody != nullptr)
		rigidBody->FixedUpdate(deltaTime);

	if (isJump && position.y >= 0.f)
	{
		isJump = false;
		position.y = 0.f;

		rigidBody->SetGround(true);
		SetPosition(position);
	}
}

void TestPlayer::LateUpdate(const float& deltaTime)
{
}
