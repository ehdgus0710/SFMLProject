#pragma once

class Camera
{
protected:
	sf::View		camera;
	sf::Vector2f	cameraPosition;

	CameraType		type;

public:
	void SetViewInfo(const sf::View& view) { camera = view; }
	const sf::View& GetView() { return camera; }

	void SetCameraPosition(const sf::Vector2f& position);
	sf::Vector2f GetCameraPosition() { return cameraPosition; }

	const CameraType& GetCameraType() const { return type; }

public:
	Camera(CameraType type);
	Camera(const sf::View& view, CameraType type);

	virtual ~Camera();
};

