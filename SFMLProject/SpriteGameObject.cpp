#include "stdafx.h"
#include "SpriteGameObject.h"


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

void SpriteGameObject::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	GameObject::Render(renderWindow);
}

void SpriteGameObject::Reset()
{
	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId));
	SetOrigin(originPreset);
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
}

void SpriteGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
}
