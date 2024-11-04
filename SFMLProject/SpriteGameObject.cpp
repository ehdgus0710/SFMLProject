#include "stdafx.h"
#include "SpriteGameObject.h"
#include "Collider.h"


SpriteGameObject::SpriteGameObject(const std::string& texId, const std::string& name)
	:textureId(texId)
	, GameObject(name)
{
}


void SpriteGameObject::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void SpriteGameObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale);

	if (collider != nullptr)
	{
		collider->SetScale((sf::Vector2f)sprite.getTexture()->getSize() * scale );
	}
}

void SpriteGameObject::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(rotation);

	/*if (collider != nullptr)
	{
		collider->SetScale((sf::Vector2f)sprite.getTexture()->getSize() * scale);
	}*/
}

void SpriteGameObject::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	GameObject::Render(renderWindow);
}

void SpriteGameObject::Start()
{
	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId));
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);

	if (collider != nullptr)
		collider->Reset();
}

void SpriteGameObject::Update(const float& deltaTime)
{
	GameObject::Update(deltaTime);
}

void SpriteGameObject::FixedUpdate(const float& deltaTime)
{
	GameObject::FixedUpdate(deltaTime);
}

void SpriteGameObject::LateUpdate(const float& deltaTime)
{
	GameObject::LateUpdate(deltaTime);
}

void SpriteGameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
	if (collider != nullptr)
		collider->SetOrigin(preset);
}

void SpriteGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
}
