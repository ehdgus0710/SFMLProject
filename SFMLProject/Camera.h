#pragma once

class Camera : public Entity
{
protected:
	sf::View		camera;
	sf::Vector2f	cameraPosition;

	sf::FloatRect	cameraLimitRect;

	CameraType		type;
	GameObject*		followTarget;

	sf::Vector2f	followSpeed;
	float			speed;
	float			followTime;
	float			currentFollowTime;

	bool			isActive;
	bool			useFollowTarget;
	bool			useCameraLimit;
	bool			useLerpFollowTarget;

public:
	void SetActive(bool active) { isActive = active; }
	bool IsActive() { return isActive; }

public:
	void SetViewInfo(const sf::View& view) { camera = view; }
	const sf::View& GetView() { return camera; }

	void SetCameraPosition(const sf::Vector2f& position);
	sf::Vector2f GetCameraPosition() { return cameraPosition; }

	const CameraType& GetCameraType() const { return type; }
	void SetFollowTarget(GameObject* traget, bool useLerpFollow = false) { followTarget = traget; useFollowTarget = true; useLerpFollowTarget = useLerpFollow; }

	void UseFollowTarget(bool isFollowTarget) { useFollowTarget = isFollowTarget; }

	void SetFollowTime(float time) { followTime = time; }
	float GetFollowTime() const { return followTime; }

public:
	void Update(const float& deltaTime);
	virtual bool Save() const { return true; };
	virtual bool Load() { return true; };
public:
	Camera(CameraType type);
	Camera(const sf::View& view, CameraType type);

	virtual ~Camera();
};

