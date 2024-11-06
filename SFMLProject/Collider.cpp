#include "stdafx.h"
#include "Collider.h"
#include "CollisionRectangle.h"
#include "CollisionPoint.h"
#include "CollisionCircle.h"

int Collider::globalCount = 0;

Collider::Collider(ColliderType colliderType, ColliderLayer colliderLayer, sf::Vector2f offset, sf::Vector2f size)
	: active(true)
	, collision(nullptr)
	, colliderLayer(colliderLayer)
	, collisionCount(0)
	, iD(globalCount++)
	, isDestory(false)
{
	CreateCollision(colliderType, offset, size);
}

Collider::Collider(const Collider& other)
	: active(true)
	, colliderLayer(colliderLayer)
	, collisionCount(0)
	, iD(globalCount++)
	, isDestory(false)
	, owner(nullptr)
{
	ColliderType colliderType = other.collision->GetColliderType();
	if (ColliderType::Rectangle == colliderType)
		collision = new CollisionRectangle(other.colliderScale);
	else if (ColliderType::Circle == colliderType)
		collision = new CollisionCircle(other.colliderScale.x);
	else
		collision = new CollisionPoint();

	offsetPosition = other.offsetPosition;
	ColliderManager::GetInstance().AddCollider(this, colliderLayer);
}

Collider::~Collider()
{
	if (collision != nullptr)
		delete collision;
}

void Collider::OnDestory()
{
	isDestory = true;
	SetActive(false);
}

bool Collider::IsDestory()
{
	return isDestory;
}

void Collider::SetOffsetPosition(const sf::Vector2f& offset)
{
	offsetPosition = offset;
	collision->SetPosition(position + offsetPosition);
}

void Collider::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	collision->SetPosition(position + offsetPosition);
}

void Collider::SetOrigin(const sf::Vector2f& origin)
{
}

void Collider::SetOrigin(const Origins& origins)
{
	collision->SetOrigin(origins);
}

sf::Vector2f Collider::GetPosition()
{
	return collision->GetPosition();
}

sf::Vector2f Collider::GetScale()
{
	return collision->GetScale();
}

void Collider::SetRotation(float angle)
{
	colliderRotation = angle;
	collision->SetRotation(angle);
}

float Collider::GetRotation()
{
	return collision->GetRotation();
}

void Collider::SetScale(sf::Vector2f size)
{
	collision->SetScale(size);
}

void Collider::Reset()
{
	collisionTagetVector.clear();
	collision->Reset();
	isDestory = false;
	SetActive(true);
}

void Collider::CreateCollision(ColliderType colliderType, sf::Vector2f offset, sf::Vector2f size)
{
	if (ColliderType::Rectangle == colliderType)
		collision = new CollisionRectangle(size);
	else if (ColliderType::Circle == colliderType)
		collision = new CollisionCircle(size.x);
	else
		collision = new CollisionPoint();

	offsetPosition = offset;
	ColliderManager::GetInstance().AddCollider(this, colliderLayer);
}

void Collider::Render(sf::RenderWindow& renderWindow)
{
	collision->Render(renderWindow);
}

void Collider::OnCollisionEnter(Collider* target)
{
	collisionTagetVector.push_back(target);
	collision->IsCollision();
	owner->OnCollisionEnter(target);
}

void Collider::OnCollisionStay(Collider* target)
{
	owner->OnCollisionStay(target);
}

void Collider::OnCollisionEnd(Collider* target)
{
	owner->OnCollisionEnd(target);
	collision->EndCollision();
	if(!isDestory)
		collisionTagetVector.erase(std::find(collisionTagetVector.begin(), collisionTagetVector.end(), target));
}

ColliderType Collider::GetColliderType()
{
	return collision->GetColliderType();
}
