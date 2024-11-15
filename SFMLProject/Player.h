#pragma once
#include "GameObject.h"
#include "PlayerFSM.h"

class Rigidbody;

struct PlayerStatus
{
	int			maxHp;
	int			hp;
	float		speed;
	float		jumpPower;
	float		maxJumpPower;

	PlayerStatus() {}
	PlayerStatus(int hp, float speed, float jumpPower, float maxJumpPower)
		: hp(hp), maxHp(hp), speed(speed), jumpPower(jumpPower), maxJumpPower(maxJumpPower) {}
};

class Player : public GameObject
{
protected:
	sf::Sprite	sprite;
	PlayerFSM	fsm;

	sf::Vector2f	moveDirection;
	PlayerStatus	currentStatus;

	bool			isJump;
	bool			isHit;
	bool			isDead;
	bool			isFlipX;

public:
	void InputMove();
	void InputJump();
	void TakeDamage();
	void OnFlipX();
	bool IsFlipX() { return isFlipX; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
public:
	void CreateAnimator() override;
	float GetSpeed() { return currentStatus.speed; }


public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;


	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	Player(const std::string& name = "Player");
	virtual ~Player();
	Player& operator= (const Player& other) = delete;
};

