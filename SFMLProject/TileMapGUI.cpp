#include "stdafx.h"
#include "TileMapGUI.h"
#include "imgui.h"
#include "TileMap.h"

TileMapGUI::TileMapGUI()
	: ComponentGUI(ComponentGUIType::TileMap)
	, tileMap(nullptr)
	, isTileMapEditor(false)
{
}

TileMapGUI::~TileMapGUI()
{
}

void TileMapGUI::update()
{
	if (tileMap == nullptr)
		return;

	// ImGui::line(0.f,100.f);
	// ImGui::Text("TileMap"); 

	ImGui::BeginChild("##TileMap", { 300.f,300.f });
	ImGui::SeparatorText("TileMap");

	//auto name = GetName().c_str();
	sf::Vector2f cellSize = tileMap->GetCellSize();
	float cellSizeArr[2] = { cellSize.x, cellSize.y };

	sf::Vector2u tileCount = tileMap->GetTileCount();
	int tileCountArr[2] = { (int)tileCount.x, (int)tileCount.y };

	// tileMap->SetTileInfo

	ImGui::Text("CellSize"); ImGui::SameLine();
	if (ImGui::InputFloat2("##CellSize", cellSizeArr))
	{
		if (cellSizeArr[0] > 0.f && cellSizeArr[1] > 0.f)
		{
			cellSize.x = cellSizeArr[0];
			cellSize.y = cellSizeArr[1];
			tileMap->SetCellSize(cellSize);
		}
	}
	ImGui::Text("TileCount"); ImGui::SameLine();
	if (ImGui::InputInt2("##TileCount", tileCountArr))
	{
		if (tileCountArr[0] > 0 && tileCountArr[1] > 0)
		{
			tileCount.x = tileCountArr[0];
			tileCount.y = tileCountArr[1];
			tileMap->SetTileCount(tileCount);
		}

	}

	texture = tileMap->GetTexture();
	auto textureSize = texture->getSize();

	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
	//ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	//ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);

	ImGui::Image(*texture, { (float)textureSize.x, (float)textureSize.y });
	OnTileMapEditor();
	/*ImGui::Text("Rotation"); ImGui::SameLine();
	if (ImGui::InputFloat("##Rotation", &rotation))
	{
		targetObject->SetRotation(rotation);
	}

	ImGui::Text("Origin"); ImGui::SameLine();
	if (ImGui::InputFloat2("##Origin", originArr))
	{
		origin = { originArr[0], originArr[1] };
		targetObject->SetOrigin(origin);
	}*/


	ImGui::EndChild();
}

void TileMapGUI::SetObject(GameObject* object)
{
	target = object;
	tileMap = (TileMap*)target;
}

void TileMapGUI::TileMapEditor()
{

	//renderTexture.create(texture.getSize().x, texture.getSize().y);

	



}
void TileMapGUI::OnTileMapEditor()
{
	bool b = ImGui::Button("Edit##MapTool");
	if (b)
	{
		isTileMapEditor = true;
	}
	/*if ()
	{
		isTileMapEditor != isTileMapEditor;
	}*/
	if (isTileMapEditor)
	{
		ImGui::Begin(tileMap->GetName().c_str(), &isTileMapEditor);

		ImGui::Text("Tile LB = Select , RB = cancel");

		sf::Vector2f cellSize = tileMap->GetCellSize();
		sf::Vector2u tileTextureSize = tileMap->GetTileTextrueSize();;
		ImGuiIO& io = ImGui::GetIO();

		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImVec2 uv0 = {};
		ImVec2 uv1 = {};
		ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		int frame_padding = -1;

		auto texSize = texture->getSize();

		sf::Vector2f size = sf::Vector2f(texSize.x, texSize.y);
		int heightSize = texSize.y / cellSize.y;
		int widthSize = texSize.x / cellSize.x;

		if (ImGui::ImageButton(tileMap->GetName().c_str(), *texture, size))
		{

		}
		ImGui::End();

		/*for (int i = 0; i < heightSize; ++i)
		{
			for (int j = 0; j < widthSize; ++j)
			{
				ImGui::PushID(i * heightSize + j);
				uv0 = ImVec2(tileTextureSize.x * j, tileTextureSize.y * i);
				uv1 = ImVec2(uv0.x + tileTextureSize.x, uv0.y + tileTextureSize.y);

				if ()
				{
					m_tIndex.iIndexPosX = j;
					m_tIndex.iIndexPosY = i;
					m_tIndex.vUVStartPos.x = uv0.x;
					m_tIndex.vUVStartPos.y = uv0.y;

					m_bSelect = true;
				}
				ImGui::SameLine();

				ImGui::PopID();
			}
			ImGui::NewLine();
		}

		if (TileMapDomain() && KEY_HOLD(KEY::LBTN) && m_bSelect)
		{
			pTileMap->SetIndexInfoPos(m_tIndex, int(vTilePos.y) * iYFace + int(vTilePos.x));
			vector<tIndexInfo> vecIndex = pTileMap->GetIndexInfo();

		}
		if (KEY_TAP(KEY::RBTN))
		{
			m_bSelect = false;
		}
		ImGui::End();*/
	}
}
void render_grid(sf::RenderTexture& renderTexture)
{
	sf::Vertex line[2];
	for (int i = 0; i <= renderTexture.getSize().y; i += 32)
	{
		line[0] = sf::Vector2f(0, i);
		line[1] = sf::Vector2f(renderTexture.getSize().x, i);
		renderTexture.draw(line, 2, sf::Lines);
	}

	for (int i = 0; i <= renderTexture.getSize().x; i += 32)
	{
		line[0] = sf::Vector2f(i, 0);
		line[1] = sf::Vector2f(i, renderTexture.getSize().y);
		renderTexture.draw(line, 2, sf::Lines);
	}
}
void process_imgui(sf::RenderWindow& window, sf::RenderTexture& renderTexture, sf::Sprite& sprite)
{
	//ImGui::SetNextWindowPos(ImVec2{ 251, 20 });
	ImGui::SetNextWindowSize(ImVec2{ static_cast<float>(window.getSize().x - 251.0f), static_cast<float>(window.getSize().y - 20.0f) });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Tileset", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysHorizontalScrollbar);

	renderTexture.clear();
	renderTexture.draw(sprite);
	render_grid(renderTexture);

	//float x = (ImGui::GetWindowSize().x - static_cast<float>(renderTexture.getSize().x)) * 0.5f; //doesn't draw grid correctly
	float x = (ImGui::GetWindowSize().x - static_cast<float>(renderTexture.getSize().x)) * 0.499f; //draws grid correctly
	ImVec2 imagePosition(x, 20.0f);
	ImGui::SetCursorPos(imagePosition);
	ImGui::Image(renderTexture, ImVec2(static_cast<float>(renderTexture.getSize().x), static_cast<float>(renderTexture.getSize().y)));

	static bool saveToFile = true;
	if (saveToFile)
	{
		sf::Image image(renderTexture.getTexture().copyToImage());
		image.saveToFile("correct.png");
		saveToFile = false;
	}

	ImGui::End();
	ImGui::PopStyleVar();
}