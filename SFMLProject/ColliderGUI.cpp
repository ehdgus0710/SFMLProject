#include "stdafx.h"
#include "ColliderGUI.h"
#include "imgui.h"


ColliderGUI::ColliderGUI()
	: ComponentGUI(ComponentGUIType::Collider)
	, collider(nullptr)
{
}

ColliderGUI::~ColliderGUI()
{
}

void ColliderGUI::Update()
{
	if (collider == nullptr)
		return;
	ImGui::Text("TileMap"); ImGui::SameLine();
	ImGui::BeginChild("##TileMap", { 300.f,300.f });

	ImGui::EndChild();
}

void ColliderGUI::SetObject(GameObject* object)
{
}
