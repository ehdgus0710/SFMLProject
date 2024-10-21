#include "stdafx.h"
#include "Collider.h"
#include "CollisionRectangle.h"
#include "CollisionPoint.h"
#include "CollisionCircle.h"

int Collider::globalCount = 0;

Collider::Collider()
	: active(true)
	, collision(nullptr)
	, collisionCount(0)
	, iD(globalCount++)
{
}

Collider::~Collider()
{
	if (collision != nullptr)
		delete collision;
}

void Collider::SetPosition(sf::Vector2f pos)
{
	position = pos + offsetPosition;
	collision->SetPosition(position);
}

sf::Vector2f Collider::GetPosition()
{
	return collision->GetPosition();
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
	ColliderManager::GetInstance().AddCollider(this);
}

void Collider::OnCollisionEnter(Collider* target)
{
}

void Collider::OnCollisionStay(Collider* target)
{
}

void Collider::OnCollisionEnd(Collider* target)
{
}

ColliderType Collider::GetColliderType()
{
	return collision->GetColliderType();
}
