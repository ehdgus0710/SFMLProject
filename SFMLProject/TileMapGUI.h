#pragma once

#include "ComponentGUI.h"

class TileMap;

class TileMapGUI : public ComponentGUI
{
protected:
	TileMap* tileMap;
	sf::RenderTexture renderTexture;
	sf::Texture* texture;
	sf::Sprite sprite;

	bool isTileMapEditor;
public:
	void update() override;
	void SetObject(GameObject* object) override;
	void TileMapEditor();

	void OnTileMapEditor();
public:
	TileMapGUI();
	~TileMapGUI();
};

