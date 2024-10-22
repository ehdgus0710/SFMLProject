#pragma once
#include "UIGameObject.h"
class UITextGameObject : public UIGameObject
{
protected:
	sf::Text		scoreText;
	std::string		textId;
	std::string		textString;
	sf::Color		textColor;
	unsigned int	textSize;

public:
	void Init() override;
	void Reset() override;
	void Render(sf::RenderWindow& window) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetString(const std::string& string);	
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
public:
	UITextGameObject(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor = sf::Color::White);
	virtual ~UITextGameObject() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	UITextGameObject& operator= (const UITextGameObject& other) = delete;
};

