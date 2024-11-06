#pragma once

class TileMap : public GameObject
{
protected:
	sf::VertexArray		vertexArray;
	sf::RenderStates	renderState;
	std::string			spriteSheetId;

	sf::Texture*		texture;
	sf::Transform		transform;

	sf::Vector2u		cellCount;
	sf::Vector2f		cellSize;

public:

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void ChangeTextureTile(std::string tileID);

	void SetTileInfo(std::string textId, const sf::Vector2u& tileCount, const sf::Vector2f& tileSize, const sf::Vector2u textTileSize);
	void UpdateTransform();

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	const sf::Vector2f& GetCellSize() const { return cellSize; }

public:
	void Awake() override;
	void Release() override;
	void Start() override;
	void Render(sf::RenderWindow& window) override;
public:
	TileMap(const std::string& TileId, const std::string& name = "");
	~TileMap() = default;

};