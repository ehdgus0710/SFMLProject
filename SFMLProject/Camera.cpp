#include "stdafx.h"
#include "Camera.h"

Camera::Camera(CameraType type)
	: type(type)
	 , isActive(true)
{
}

Camera::Camera(const sf::View& view, CameraType type)
	: type(type)
	, isActive(true)
{
	camera = view;
	cameraPosition = camera.getCenter();
}

Camera::~Camera()
{
}

void Camera::SetCameraPosition(const sf::Vector2f& position)
{
	cameraPosition = position; 
	camera.setCenter(cameraPosition);
}