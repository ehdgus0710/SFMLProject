#include "stdafx.h"
#include "ColliderManager.h"

#include "Collider.h"
#include "Collision.h"

void ColliderManager::Init()
{
}

void ColliderManager::Update()
{
    for (int i = 0; i < vectorSize - 1; ++i)
    {
        for (int j = i + 1; j <= vectorSize; ++j)
        {
            if (colliderVector[i]->GetActive() || colliderVector[j]->GetActive())
                continue;

            if (CheckCollision(colliderVector[i], colliderVector[j]))
            {
                uint64_t getID = colliderVector[i]->GetID() * colliderVector[j]->GetID();
                auto iter = collisionMap.find(getID);
                if (iter == collisionMap.end())
                    collisionMap.insert({ getID , true });
                else
                {
                    collisionMap[getID] = true;
                }
            }
        }
    }

}

bool ColliderManager::CheckCollision(Collider* left, Collider* right)
{
    return false;
}

void ColliderManager::AddCollider(Collider* newCollision)
{
    colliderVector.push_back(newCollision);
    vectorSize = colliderVector.size();
}
