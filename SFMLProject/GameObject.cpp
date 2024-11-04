#include "stdafx.h"
#include "GameObject.h"
#include "Collider.h"

GameObject::GameObject(const std::string& name)
    : name(name)
	, originPreset(Origins::MiddleCenter)
	, collider(nullptr)
	, rotation(0.f)
	, scale(sf::Vector2f::one)
	, position(sf::Vector2f::zero)
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

void GameObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	if (collider != nullptr)
		collider->SetScale(scale);
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

void GameObject::Awake()
{
}

void GameObject::Start()
{
	if (collider != nullptr)
		collider->Reset();
}

void GameObject::Release()
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

bool GameObject::CreateCollider(ColliderType colliderType, ColliderLayer colliderLayer, sf::Vector2f offset, sf::Vector2f size)
{
	if (collider == nullptr)
	{
		collider = new Collider(colliderType, colliderLayer, offset, size);
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