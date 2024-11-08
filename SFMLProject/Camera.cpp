#include "stdafx.h"
#include "Camera.h"

Camera::Camera(CameraType type)
	: type(type)
	, isActive(true)
	, followTarget(nullptr)
	, useCameraLimit(false)
	, useFollowTarget(false)
{
}

Camera::Camera(const sf::View& view, CameraType type)
	: type(type)
	, isActive(true)
	, followTarget(nullptr)
	, useCameraLimit(false)
	, useFollowTarget(false)
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


void Camera::Update(const float& deltaTime)
{
	if (useFollowTarget)
	{
		if (followTarget != nullptr)
		{
			if (useLerpFollowTarget)
			{
				cameraPosition = sf::Vector2f::SmoothDamp(cameraPosition, followTarget->GetPosition(), followSpeed, 0.5f, 400.f, deltaTime);
				// cameraPosition += sf::Vector2f::Normalized(followTarget->GetPosition(), cameraPosition) * 400.f * deltaTime;
				if (sf::Vector2f::Distance(cameraPosition, followTarget->GetPosition()) <= 1.f)
					cameraPosition = followTarget->GetPosition();

				camera.setCenter(cameraPosition);
				
			}
			else
			{
				cameraPosition = followTarget->GetPosition();
				camera.setCenter(cameraPosition);
			}
			
		}
	}

	if (useCameraLimit)
	{
		cameraPosition = sf::Vector2f::Clamp(cameraPosition, { cameraLimitRect.left,  cameraLimitRect.top }, { cameraLimitRect.width, cameraLimitRect.height });
		camera.setCenter(cameraPosition);
	}
	
}
