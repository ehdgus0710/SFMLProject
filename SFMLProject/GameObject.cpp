#include "stdafx.h"
#include "GameObject.h"
#include "Collider.h"

GameObject::GameObject(const std::string& name)
    : name(name)
	, originPreset(Origins::MiddleCenter)
	, collider(nullptr)
{
}

GameObject::~GameObject()
{
	if (collider != nullptr)
		delete collider;
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

void GameObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	if (collider != nullptr)
		collider->SetPosition(position);
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
	if(collider != nullptr)
		collider->SetPosition(position);
}

void GameObject::FixedUpdate(const float& deltaTime)
{
}

void GameObject::LateUpdate(const float& deltaTime)
{
}

void GameObject::Render(sf::RenderWindow& renderWindow)
{
	if(collider != nullptr)
		collider->Render(renderWindow);
}

bool GameObject::CreateCollider(ColliderType colliderType, sf::Vector2f offset, sf::Vector2f size)
{
	if (collider == nullptr)
	{
		collider = new Collider(colliderType, offset, size * 100.f);
		collider->SetPosition(position);
		return true;
	}

	return false;
}

bool GameObject::Save() const
{
    return false;
}

bool GameObject::Load()
{
    return false;
}