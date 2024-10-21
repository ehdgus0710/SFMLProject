#pragma once

class Collision;
class Collider;

class ColliderManager : public Singleton<ColliderManager>
{
	friend Singleton<ColliderManager>;
private:
	std::unordered_map<int, bool> collisionMap;

	// юс╫ц
	std::vector<Collider*> colliderVector;
	int vectorSize;
		
public:
	void Init();
	void Update();
	//bool isCo
	bool CheckCollision(Collider* left, Collider* right);
	void AddCollider(Collider* newCollision);

protected:
	ColliderManager() = default;
	~ColliderManager() override {};
	ColliderManager(const ColliderManager&) = delete;
	ColliderManager& operator=(const ColliderManager&) = delete;
};

