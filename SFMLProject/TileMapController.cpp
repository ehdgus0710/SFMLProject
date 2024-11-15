#include "stdafx.h"
#include "TileMapController.h"

TileMapController::TileMapController(const std::string& name)
    : GameObject(name)
{
}

TileMapController::~TileMapController()
{
}


void TileMapController::AddTileMap(int count)
{
}

bool TileMapController::SaveCsv(const std::string& filePath) const
{
    return false;
}

bool TileMapController::LoadCsv(const std::string& filePath)
{
    return false;
}

sf::FloatRect TileMapController::GetLocalBounds() const
{
    return sf::FloatRect();
}

sf::FloatRect TileMapController::GetGlobalBounds() const
{
    return sf::FloatRect();
}
