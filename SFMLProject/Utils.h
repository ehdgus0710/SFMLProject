#pragma once
class Utils
{
private:
	static std::mt19937 generator;

public:
	const static float PI;

public:
	static void Init();

	static float RandomRange(float min, float max);
	static int RandomRange(int min, int max);
	static float RandomValue();				// 확률 구현 할때 자주 사용
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();

	static float Clamp(float value, float min, float max);
	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& object, Origins preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& object, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& object, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& object, Origins preset);
};

