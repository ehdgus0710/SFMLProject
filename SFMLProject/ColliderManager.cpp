#include "stdafx.h"
#include "ColliderManager.h"

#include "Collider.h"
#include "Collision.h"

#include "CollisionCircle.h"
#include "CollisionRectangle.h"

void ColliderManager::Init()
{
}

void ColliderManager::Update()
{
    for (int i = 0; i < vectorSize - 1; ++i)
    {
        for (int j = i + 1; j < vectorSize; ++j)
        {
            if (!colliderVector[i]->GetActive() || !colliderVector[j]->GetActive())
                continue;

            auto left = colliderVector[i]->GetID() < colliderVector[j]->GetID() ? colliderVector[i]->GetID() : colliderVector[j]->GetID();
            auto right = colliderVector[i]->GetID() < colliderVector[j]->GetID() ? colliderVector[j]->GetID() : colliderVector[i]->GetID();
            std::string hash = std::to_string(left) + "," + std::to_string(right);

            auto iter = collisionMap.find(hash);
            if (iter == collisionMap.end())
            {
                collisionMap.insert({ hash , false });
                iter = collisionMap.find(hash);
            }

			if (CheckCollision(colliderVector[i], colliderVector[j]))
			{
                // 충돌하지 않음
                if (!iter->second)
                {
                    colliderVector[i]->OnCollisionEnter(colliderVector[j]);
                    colliderVector[j]->OnCollisionEnter(colliderVector[i]);
                    iter->second = true;
                }
                else
                {
                    colliderVector[i]->OnCollisionStay(colliderVector[j]);
                    colliderVector[j]->OnCollisionStay(colliderVector[i]);
                }
			}
            else
            {
                if (iter->second)
                {
                    colliderVector[i]->OnCollisionEnd(colliderVector[j]);
                    colliderVector[j]->OnCollisionEnd(colliderVector[i]);
                    iter->second = false;
                }
            }
		}
	}

}

bool ColliderManager::CheckCollision(Collider* left, Collider* right)
{
    if (left->GetColliderType() == ColliderType::Rectangle)
    {
        if (right->GetColliderType() == ColliderType::Rectangle)
            return IsRectToRectCollision(left, right);
        else if (right->GetColliderType() == ColliderType::Circle)
            return IsCircleToRectCollision(right, left);
        else
            return IsPointToRectCollision(right, left);

    }
    else if (left->GetColliderType() == ColliderType::Circle)
    {
        if (right->GetColliderType() == ColliderType::Rectangle)
            return IsCircleToRectCollision(left, right);
        else if (right->GetColliderType() == ColliderType::Circle)
            return IsCircleToCircleCollision(left, right);
        else
            return IsCircleToPointCollision(left, right);
    }
    else
    {
        if (right->GetColliderType() == ColliderType::Rectangle)
            return IsPointToRectCollision(left, right);
        else if (right->GetColliderType() == ColliderType::Circle)
            return IsCircleToPointCollision(right, left);
        else
            return IsPointToPointCollision(left, right);
    }

    return false;
}

void ColliderManager::AddCollider(Collider* newCollision)
{
    colliderVector.push_back(newCollision);
    vectorSize = (int)colliderVector.size();
}

bool ColliderManager::IsPointToPointCollision(Collider* left, Collider* right)
{
    float distance = sf::Vector2f::Distance(left->GetCollision()->GetPosition(), right->GetCollision()->GetPosition());

    return distance < 1.f ? true : false;
}

bool ColliderManager::IsCircleToCircleCollision(Collider* left, Collider* right)
{
    float distance = sf::Vector2f::Distance(left->GetCollision()->GetPosition(), right->GetCollision()->GetPosition());
    float lenght = ((CollisionCircle*)left->GetCollision())->GetRadian() + ((CollisionCircle*)right->GetCollision())->GetRadian();
    return distance < lenght ? true : false;
}

bool ColliderManager::IsRectToRectCollision(Collider* left, Collider* right)
{
    CollisionRectangle* leftRectangleCollision = (CollisionRectangle*)left->GetCollision();
    CollisionRectangle* rightRectangleCollision = (CollisionRectangle*)right->GetCollision();
    //
    //sf::Vector2f leftRectangleRightVector = leftRectangleCollision->GetLeftTopPosition() - leftRectangleCollision->GetRightTopPosition();
    //sf::Vector2f leftRectangleDirVector = leftRectangleCollision->GetLeftTopPosition() - leftRectangleCollision->GetPosition();
    //leftRectangleDirVector.Normalized();
    //float dot = sf::Vector2f::Dot(leftRectangleRightVector, leftRectangleDirVector);
    //
    //sf::Vector2f rightRectangleUpVector = rightRectangleCollision->GetLeftTopPosition() - rightRectangleCollision->GetRightTopPosition();
    //sf::Vector2f leftRectangleDirVector = leftRectangleCollision->GetLeftTopPosition() - leftRectangleCollision->GetPosition();

    //RectA.Left < RectB.Right&& RectA.Right > RectB.Left&& RectA.Top > RectB.Bottom&& RectA.Bottom < RectB.Top
   /* 
    if (leftRectangleCollision->GetLeftPosition() < rightRectangleCollision->GetRightPosition()
        && leftRectangleCollision->GetRightPosition() > rightRectangleCollision->GetLeftPosition()
        && leftRectangleCollision->GetTopPosition() > rightRectangleCollision->GetBottomPosition()
        && leftRectangleCollision->GetBottomPosition() > rightRectangleCollision->GetTopPosition())
        return false;*/

    // AABB
    if ((left->GetScale().x + right->GetScale().x) * 0.5f < abs(left->GetPosition().x - right->GetPosition().x))
        return false;
    
    if ((left->GetScale().y + right->GetScale().y) * 0.5f < abs(left->GetPosition().y - right->GetPosition().y))
        return false;


    return true;
}
bool ColliderManager::IsCircleToRectCollision(Collider* left, Collider* right)
{
    //sf::Vector2f circlePosition = left->GetCollision()->GetPosition();
    //sf::Vector2f rectanglePosition = right->GetCollision()->GetPosition();
    //float radian = ((CollisionCircle*)left->GetCollision())->GetRadian();

    //CollisionRectangle* rectangleCollision = (CollisionRectangle*)right->GetCollision();
    //sf::Vector2f distance = sf::Vector2f::Distance(circlePosition, rectanglePosition);
    //sf::Vector2f rectangleSize = rectangleCollision->GetScale() * 0.5f;


    //if (circlePosition.x < rectanglePosition.x)
    //{
    //    if (circlePosition.y < rectanglePosition.y)
    //    {
    //        //  x 음수, y 는 양수
    //        return distance.x < (rectangleSize.x + radian) * -1.f && distance.y < rectangleSize.y + radian;
    //    }
    //    else
    //    {
    //        //  x 음수, y 는 음수
    //        distance = rectangleCollision->GetLeftTopPosition() - rectanglePosition;
    //        return distance.x < (rectangleSize.x + radian) * -1.f && distance.y < (rectangleSize.y + radian) * -1.f;
    //    }
    //}
    //else
    //{
    //    if (circlePosition.y < rectanglePosition.y)
    //    {
    //        // x 양수,  y 는 음수
    //        distance = rectangleCollision->GetRightTopPosition() - rectanglePosition;
    //        return distance.x < rectangleSize.x + radian && distance.y < (rectangleSize.y + radian) * -1.f;
    //    }
    //    else
    //    {
    //        // x 양수,  y 는 양수
    //        distance = rectangleCollision->GetRightBottomPosition() - rectanglePosition;
    //        return distance.x < rectangleSize.x + radian && distance.y < rectangleSize.y + radian;
    //    }
    //}

    return false;
}

bool ColliderManager::IsPointToRectCollision(Collider* left, Collider* right)
{
    sf::Vector2f distance = left->GetCollision()->GetPosition() - right->GetCollision()->GetPosition();
    sf::Vector2f rectangleSize = ((CollisionRectangle*)right->GetCollision())->GetScale() * 0.5f;

    return distance.x < rectangleSize.x && distance.y < rectangleSize.y;
}

bool ColliderManager::IsCircleToPointCollision(Collider* left, Collider* right)
{
    float distance = sf::Vector2f::Distance(left->GetCollision()->GetPosition(), right->GetCollision()->GetPosition());
    float radian = ((CollisionCircle*)left->GetCollision())->GetRadian();

    return distance < radian ? true : false;
}