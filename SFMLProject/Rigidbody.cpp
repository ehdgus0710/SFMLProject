#include "stdafx.h"
#include "Rigidbody.h"
#include "PhysicsManager.h"

Rigidbody::Rigidbody(GameObject* owner)
	: mass(1.f)
	, isGround(true)
	, dropSpeed(0.f)
	, maxDropSpeed(200.f)
	, owner(owner)
	, friction(false)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::SetVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

void Rigidbody::AddForce(const sf::Vector2f& force)
{
	this->force += force * mass;
}

void Rigidbody::SetGround(bool isGround)
{
	this->isGround = isGround;
}

void Rigidbody::FixedUpdate(const float& fixedDeltaTime)
{
	//velocity = accel * fixedDeltaTime;

	if (!isGround)
	{
		dropSpeed += 9.8f * fixedDeltaTime * 5.f;
		velocity.y += dropSpeed;
	}
	else
	{
		dropSpeed = 0.f;
		velocity.y = 0.f;
	}

	owner->SetPosition(owner->GetPosition() + velocity * fixedDeltaTime);
}
void Rigidbody::Awake()
{
}

void Rigidbody::Start()
{
}

bool Rigidbody::Save() const
{
	return false;
}

bool Rigidbody::Load()
{
	return false;
}

bool Rigidbody::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool Rigidbody::LoadCsv(const std::string& filePath)
{
	return false;
}
