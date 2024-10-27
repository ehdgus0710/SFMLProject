#pragma once

class Collision;
class Collider;

class ColliderManager : public Singleton<ColliderManager>
{
	friend Singleton<ColliderManager>;
private:
	std::unordered_map<std::string, bool> collisionMap;

	// юс╫ц
	std::vector<std::vector<Collider*>>  colliderVector;
	std::vector<std::vector<bool>> collisionCheckVector;
	int vectorSize;
		
public:
	void Init();
	void Update();

	void Clear();

	void LayerCollision(int left, int right);
	bool CheckCollision(Collider* left, Collider* right);
	void SetCollisionCheck(ColliderLayer left, ColliderLayer right);

	void AddCollider(Collider* newCollision, ColliderLayer right);

	bool IsPointToPointCollision(Collider* left, Collider* right);
	bool IsRectToRectCollision(Collider* left, Collider* right);
	bool IsCircleToCircleCollision(Collider* left, Collider* right);

	bool IsCircleToRectCollision(Collider* left, Collider* right);
	bool IsPointToRectCollision(Collider* left, Collider* right);
	bool IsCircleToPointCollision(Collider* left, Collider* right);

protected:
	ColliderManager() = default;
	~ColliderManager() override {};
	ColliderManager(const ColliderManager&) = delete;
	ColliderManager& operator=(const ColliderManager&) = delete;
};

