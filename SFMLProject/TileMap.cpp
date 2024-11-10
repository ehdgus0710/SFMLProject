#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& TileId, const std::string& name)
	: GameObject(name)
	, texture(nullptr)
	, spriteSheetId(TileId)
{
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	UpdateTransform();
}

void TileMap::SetRotation(float angle)
{
	rotation = angle;
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
	UpdateTransform();
}

void TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		sf::FloatRect rect = GetLocalBounds();
		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
		UpdateTransform();
	}
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void TileMap::ChangeTextureTile(std::string tileID)
{
	spriteSheetId = tileID;
	this->texture = &TEXTURE_MANAGER.Get(spriteSheetId);
}

void TileMap::SetTileInfo(std::string textId, const sf::Vector2u& tileCount, const sf::Vector2f& tileSize, const sf::Vector2u textTileSize)
{
	cellCount = tileCount;
	cellSize = tileSize;

	vertexArray.clear();
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(tileCount.x * tileCount.y * 4);

	this->texture = &TEXTURE_MANAGER.Get(spriteSheetId);

	sf::Vector2f totalTileMapSize = { (sf::Vector2f)tileCount * tileSize };

	sf::Vector2u textureCount = { texture->getSize().x / textTileSize.x , texture->getSize().y / textTileSize.y };

	sf::Vector2f positionOffset[4] =
	{
		{ 0.f , 0.f }
		, { tileSize.x , 0.f }
		, { tileSize.x , tileSize.y }
		, { 0.f , tileSize.y }
	};

	sf::Vector2f textUv[4] =
	{
		{ 0.f , 0.f }
		, { (float)textTileSize.x , 0.f}
		, (sf::Vector2f)textTileSize
		, {0.f , (float)textTileSize.y }
	};

	for (int i = 0; i < (int)tileCount.y; ++i)
	{
		sf::Vector2f createPosition = totalTileMapSize * -0.5f;

		for (int j = 0; j < (int)tileCount.x; ++j)
		{
			sf::Vector2i textureIndex;
			textureIndex.x = Utils::RandomRange(0, textureCount.x - 1);
			textureIndex.y = Utils::RandomRange(0, textureCount.y - 1);

			if (i == 0 || i == tileCount.y - 1 || j == 0 || j == tileCount.x - 1)
			{
				textureIndex.y = 3;
			}

			auto quadIndex = i * tileCount.x + j;
			sf::Vector2f quadPosition(j * tileSize.y, i * tileSize.y);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				vertexArray[vertexIndex].position = quadPosition + positionOffset[k];
				vertexArray[vertexIndex].texCoords = textUv[k];
				vertexArray[vertexIndex].texCoords.x += textureIndex.x * (float)tileSize.x;
				vertexArray[vertexIndex].texCoords.y += textureIndex.y * (float)tileSize.y;
			}
		}
	}
}

void TileMap::Awake()
{
	/*sortingLayer = SortingLayers::Background;
	sortingOrder = -1;*/

	SetTileInfo(spriteSheetId, { 30,30 }, { 50.f,50.f }, { 50,50 });
	SetOrigin(Origins::MiddleCenter);
}

void TileMap::Release()
{
}

void TileMap::Start()
{
	texture = &TEXTURE_MANAGER.Get(spriteSheetId);

	position = { 300.f,300.f };
	SetScale(sf::Vector2f::one * 1.25f);
	UpdateTransform();
}

void TileMap::UpdateTransform()
{
	transform = transform.Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

sf::FloatRect TileMap::GetLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, cellCount.x * cellSize.x, cellCount.y * cellSize.y);
}

sf::FloatRect TileMap::GetGlobalBounds() const
{
	sf::FloatRect bounds = GetLocalBounds();
	return  transform.transformRect(bounds);
}

void TileMap::Render(sf::RenderWindow& window)
{
	renderState.texture = texture;
	renderState.transform = transform;

	window.draw(vertexArray, renderState);
}
