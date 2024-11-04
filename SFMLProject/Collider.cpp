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
{
	CreateCollision(colliderType, offset, size);
}

Collider::~Collider()
{
	if (collision != nullptr)
		delete collision;
}

bool Collider::GetDestory()
{
	return false;
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

void Collider::SetScale(sf::Vector2f size)
{
	collision->SetScale(size);
}

void Collider::Reset()
{
	collision->Reset();
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
	collision->IsCollision();
}

void Collider::OnCollisionStay(Collider* target)
{
}

void Collider::OnCollisionEnd(Collider* target)
{
	collision->EndCollision();
}

ColliderType Collider::GetColliderType()
{
	return collision->GetColliderType();
}
