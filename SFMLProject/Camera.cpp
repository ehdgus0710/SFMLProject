#include "stdafx.h"
#include "Camera.h"

Camera::Camera(CameraType type)
	: type(type)
{
}

Camera::Camera(const sf::View& view, CameraType type)
	: type(type)
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