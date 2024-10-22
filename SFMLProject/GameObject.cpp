#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(const std::string& name)
    : name(name)
	, originPreset(Origins::MiddleCenter)
{
}

GameObject::GameObject(const GameObject& other)
	: name(other.name)
	, position(other.position)
	, rotation(other.rotation)
	, scale(other.scale)
	, origin(other.origin)
	, originPreset(other.originPreset)
	, active(other.active)


{
}

void GameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = {};
}

void GameObject::Init()
{
}

void GameObject::Awake()
{
}

void GameObject::Start()
{
}

void GameObject::Release()
{
}

void GameObject::Reset()
{
}


void GameObject::Update(const float& deltaTime)
{
}

void GameObject::FixedUpdate(const float& deltaTime)
{
}

void GameObject::LateUpdate(const float& deltaTime)
{
}

void GameObject::Render(sf::RenderWindow& renderWindow)
{
}

bool GameObject::Save() const
{
    return false;
}

bool GameObject::Load()
{
    return false;
}