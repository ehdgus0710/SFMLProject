#pragma once


class TileMap;

class TileMapController : public GameObject
{
protected:
	std::vector<TileMap*> tileMaps;



public:
	void AddTileMap(int count);

	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
public:
	TileMapController(const std::string& name);
	virtual ~TileMapController();
};

