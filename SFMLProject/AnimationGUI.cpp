#include "stdafx.h"
#include "AnimationGUI.h"
#include "imgui.h"

AnimationGUI::AnimationGUI()
	: ComponentGUI(ComponentGUIType::Animator)
	, animator(nullptr)
{
}

AnimationGUI::~AnimationGUI()
{
}

void AnimationGUI::update()
{
	if (animator == nullptr)
		return;
	ImGui::Text("TileMap"); ImGui::SameLine();
	ImGui::BeginChild("##TileMap", { 300.f,300.f });

	ImGui::EndChild();
}

void AnimationGUI::SetObject(GameObject* object)
{
}