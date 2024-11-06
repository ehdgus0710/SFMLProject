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

void ColliderManager::DestoryColliderCheck()
{
    for (auto& destoryCollider : destoryVector)
    {
        auto targetVector = destoryCollider->GetCollisionTarget();

        for (auto& targetCollider : targetVector)
        {
            auto leftID = destoryCollider->GetID() < targetCollider->GetID() ? destoryCollider->GetID() : targetCollider->GetID();
            auto rightID = destoryCollider->GetID() < targetCollider->GetID() ? targetCollider->GetID() : destoryCollider->GetID();
            std::string hash = std::to_string(leftID) + "," + std::to_string(rightID);

            auto iter = collisionMap.find(hash);
            if (iter == collisionMap.end())
                continue;

            destoryCollider->OnCollisionEnd(targetCollider);
            targetCollider->OnCollisionEnd(destoryCollider);
            iter->second = false;
        }

        targetVector.clear();
    }

    destoryVector.clear();
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
                // 충돌하지 않음
                if (!iter->second)
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


    

    if (left->GetRotation() == 0.f && right->GetRotation() == 0.f)
    {
        if ((left->GetScale().x + right->GetScale().x) * 0.5f < abs(left->GetPosition().x - right->GetPosition().x))
            return false;

        if ((left->GetScale().y + right->GetScale().y) * 0.5f < abs(left->GetPosition().y - right->GetPosition().y))
            return false;
    }

    else
    {
        return CheckOBBCollision(left, right);
    }
}
bool ColliderManager::IsCircleToRectCollision(Collider* left, Collider* right)
{
    sf::Vector2f circlePosition = left->GetCollision()->GetPosition();
    sf::Vector2f rectanglePosition = right->GetCollision()->GetPosition();
    float radian = ((CollisionCircle*)left->GetCollision())->GetRadian();
    Rectangle rightRect = ((CollisionRectangle*)right->GetCollision())->GetRectangle();

    if ((rightRect.leftPosition <= circlePosition.x && rightRect.rightPosition >= circlePosition.x)
        || (rightRect.topPosition <= circlePosition.y && rightRect.bottomPosition >= circlePosition.y))
    {
        rightRect.leftPosition -= radian;
        rightRect.rightPosition += radian;
        rightRect.topPosition -= radian;
        rightRect.bottomPosition += radian;

        if (rightRect.leftPosition < circlePosition.x && rightRect.rightPosition > circlePosition.x
            && rightRect.topPosition < circlePosition.y && rightRect.bottomPosition > circlePosition.y)
            return true;
    }
    else
    {
        if (IsCircleToPointCollision(circlePosition, radian, { rightRect.leftPosition , rightRect.topPosition }))
            return true;
        if (IsCircleToPointCollision(circlePosition, radian, { rightRect.leftPosition , rightRect.bottomPosition }))
            return true;
        if (IsCircleToPointCollision(circlePosition, radian, { rightRect.rightPosition , rightRect.topPosition }))
            return true;
        if (IsCircleToPointCollision(circlePosition, radian, { rightRect.rightPosition , rightRect.bottomPosition }))
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

bool ColliderManager::CheckOBBCollision(Collider* left, Collider* right)
{
    CollisionRectangle* leftCollsion = ((CollisionRectangle*)left->GetCollision());
    CollisionRectangle* rightCollsion = ((CollisionRectangle*)right->GetCollision());
    Rectangle leftRect = leftCollsion->GetRectangle();
    Rectangle rightRect = rightCollsion->GetRectangle();

    auto leftTransform = leftCollsion->GetTransform();
    auto rightTransform = rightCollsion->GetTransform();

    std::vector<sf::Vector2f> leftPoints(4);
    leftPoints[0] = sf::Vector2f(leftRect.leftPosition, leftRect.topPosition);
    leftPoints[1] = sf::Vector2f(leftRect.rightPosition, leftRect.topPosition);
    leftPoints[2] = sf::Vector2f(leftRect.rightPosition, leftRect.bottomPosition);
    leftPoints[3] = sf::Vector2f(leftRect.leftPosition, leftRect.bottomPosition);

    std::vector<sf::Vector2f> rightPoints(4);
    rightPoints[0] = sf::Vector2f(rightRect.leftPosition, rightRect.topPosition);
    rightPoints[1] = sf::Vector2f(rightRect.rightPosition, rightRect.topPosition);
    rightPoints[2] = sf::Vector2f(rightRect.rightPosition, rightRect.bottomPosition);
    rightPoints[3] = sf::Vector2f(rightRect.leftPosition, rightRect.bottomPosition);

    std::vector<sf::Vector2f> axes;
    for (int i = 0; i < 4; ++i)
    {
        sf::Vector2f p1 = leftTransform.transformPoint(leftPoints[i]);
        sf::Vector2f p2 = leftTransform.transformPoint(leftPoints[(i + 1) % 4]);
        // 방향 벡터 구하기
        sf::Vector2f edge = p2 - p1;
        sf::Vector2f normal(-edge.y, edge.x);
        normal.Normalized();
        axes.push_back(normal);
    }

    for (int i = 0; i < 4; ++i)
    {
        sf::Vector2f p1 = rightTransform.transformPoint(rightPoints[i]);
        sf::Vector2f p2 = rightTransform.transformPoint(rightPoints[(i + 1) % 4]);
        sf::Vector2f edge = p2 - p1;
        sf::Vector2f normal(-edge.y, edge.x);
        normal.Normalized();
        axes.push_back(normal);
    }

    // 모든 축마다 최대 값 최소 값을 구해서 비교

    for (const auto& axis : axes)
    {
        float minA = std::numeric_limits<float>::max();
        float maxA = std::numeric_limits<float>::lowest();
        // 투영
        for (const auto& point : leftPoints)
        {
            sf::Vector2f transformedPoint = leftTransform.transformPoint(point);
            float projection = sf::Vector2f::Dot(axis, transformedPoint);
            minA = std::min(minA, projection);
            maxA = std::max(maxA, projection);
        }

        float minB = std::numeric_limits<float>::max();
        float maxB = std::numeric_limits<float>::lowest();
        for (const auto& point : rightPoints)
        {
            sf::Vector2f transformedPoint = rightTransform.transformPoint(point);
            float projection = sf::Vector2f::Dot(axis, transformedPoint);
            minB = std::min(minB, projection);
            maxB = std::max(maxB, projection);
        }

        if (maxA < minB || maxB < minA)
        {
            return false;
        }
    }
    return true;
}
