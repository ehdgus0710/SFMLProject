#include "stdafx.h"
#include "ColliderManager.h"

#include "Collider.h"
#include "Collision.h"

#include "CollisionCircle.h"
#include "CollisionRectangle.h"

ColliderManager::ColliderManager()
{
    collisionCheckVector.clear();
    colliderVector.clear();

    colliderVector.resize((int)ColliderLayer::End);
    collisionCheckVector.resize((int)ColliderLayer::End);

    for (int i = 0; i < (int)ColliderLayer::End; ++i)
    {
        collisionCheckVector[i].resize((int)ColliderLayer::End);
    }
}

void ColliderManager::Init()
{
    collisionCheckVector.clear();
    colliderVector.clear();

    colliderVector.resize((int)ColliderLayer::End);
    collisionCheckVector.resize((int)ColliderLayer::End);

    for (int i = 0; i < (int)ColliderLayer::End; ++i)
    {
        collisionCheckVector[i].resize((int)ColliderLayer::End);
    }
}

void ColliderManager::Update()
{

    for (int i = 0; i < (int)ColliderLayer::End; ++i)
    {
        for (int j = i; j < (int)ColliderLayer::End; ++j)
        {
            if (collisionCheckVector[j][i] && collisionCheckVector[i][j])
            {
                LayerCollision(i, j);
            }
        }
    }

}

void ColliderManager::Clear()
{
    colliderVector.clear();
    collisionCheckVector.clear();
    Init();
}

void ColliderManager::LayerCollision(int left, int right)
{
    int leftSize = (int)colliderVector[left].size();
    int rightSize = (int)colliderVector[right].size();

    for (int i = 0; i < leftSize; ++i)
    {
        for (int j = 0; j < rightSize; ++j)
        {
            //if (!colliderVector[left][i]->GetActive() || !colliderVector[right][j]->GetActive())
            //    continue;

            if (colliderVector[i] == colliderVector[j])
                continue;

            auto leftID = colliderVector[left][i]->GetID() < colliderVector[right][j]->GetID() ? colliderVector[left][i]->GetID() : colliderVector[right][j]->GetID();
            auto rightID = colliderVector[left][i]->GetID() < colliderVector[right][j]->GetID() ? colliderVector[right][j]->GetID() : colliderVector[left][i]->GetID();
            std::string hash = std::to_string(leftID) + "," + std::to_string(rightID);

            auto iter = collisionMap.find(hash);
            if (iter == collisionMap.end())
            {
                collisionMap.insert({ hash , false });
                iter = collisionMap.find(hash);
            }

            if (CheckCollision(colliderVector[left][i], colliderVector[right][j]))
            {
                // 사망 예정 오브젝트
                if (colliderVector[left][i]->GetDestory() || colliderVector[right][i]->GetDestory())
                {
                    colliderVector[left][i]->OnCollisionEnd(colliderVector[right][j]);
                    colliderVector[right][j]->OnCollisionEnd(colliderVector[left][i]);
                    iter->second = false;
                }
                // 충돌하지 않음
                else if (!iter->second)
                {
                    colliderVector[left][i]->OnCollisionEnter(colliderVector[right][j]);
                    colliderVector[right][j]->OnCollisionEnter(colliderVector[left][i]);
                    iter->second = true;
                }
                else
                {
                    colliderVector[left][i]->OnCollisionStay(colliderVector[right][j]);
                    colliderVector[right][j]->OnCollisionStay(colliderVector[left][i]);
                }
            }
            else
            {
                if (iter->second)
                {
                    colliderVector[left][i]->OnCollisionEnd(colliderVector[right][j]);
                    colliderVector[right][j]->OnCollisionEnd(colliderVector[left][i]);
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

void ColliderManager::SetCollisionCheck(ColliderLayer left, ColliderLayer right)
{
    collisionCheckVector[(int)left][(int)right] = true;
    collisionCheckVector[(int)right][(int)left] = true;
}

void ColliderManager::AddCollider(Collider* newCollision, ColliderLayer colliderLayer)
{
    colliderVector[(int)colliderLayer].push_back(newCollision);
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
    sf::Vector2f circlePosition = left->GetCollision()->GetPosition();
    sf::Vector2f rectanglePosition = right->GetCollision()->GetPosition();
    float radian = ((CollisionCircle*)left->GetCollision())->GetRadian();
    sf::FloatRect rightRect = ((CollisionRectangle*)right->GetCollision())->GetRect();
    auto test = ((CollisionRectangle*)right->GetCollision())->GetScale();

    if ((rightRect.left <= circlePosition.x && rightRect.width >= circlePosition.x)
        || (rightRect.top <= circlePosition.y && rightRect.height >= circlePosition.y))
    {
        rightRect.left -= radian;
        rightRect.width += radian;
        rightRect.top -= radian;
        rightRect.height += radian;

        if (rightRect.left < circlePosition.x && rightRect.width > circlePosition.x
            && rightRect.top < circlePosition.y && rightRect.height > circlePosition.y)
            return true;
    }
    else
    {
        if (IsCircleToPointCollision(circlePosition, radian, { rightRect.left , rightRect.top }))
            return true;
        if (IsCircleToPointCollision(circlePosition, radian, { rightRect.left , rightRect.height }))
            return true;
        if (IsCircleToPointCollision(circlePosition, radian, { rightRect.width , rightRect.top }))
            return true;
        if (IsCircleToPointCollision(circlePosition, radian, { rightRect.width , rightRect.height }))
            return true;
    }

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
bool ColliderManager::IsCircleToPointCollision(sf::Vector2f circlePosition, float radian, sf::Vector2f pointPosition)
{
    float distance = sf::Vector2f::Distance(circlePosition, pointPosition);

    return distance < radian ? true : false;
}
