#include "stdafx.h"
#include "AnimationToolGUI.h"
#include "imgui.h"

#include "Animation.h"
#include "Animator.h"
#include "GameObject.h"


AnimationToolGUI::AnimationToolGUI()
	: GUI("AnimationTool")
	, accTime(0.f)
	, isPlay(false)
	, isRepeat(false)
    , texture(nullptr)

{
}

AnimationToolGUI::~AnimationToolGUI()
{
}


void AnimationToolGUI::Init()
{
}

void AnimationToolGUI::Update()
{
    bool b = true;

    ImGui::Begin(GetName().c_str(), &b);

    static int item_current_idx = 0; // Here we store our selection data as an index.
    static ImGuiComboFlags flags = 0;
    static int iAnimIndexSize = 0;

    auto map = ResourcesManager<sf::Texture>::GetInstance().GetResourcesMap();

    //auto iter = map.begin();
    std::vector<std::string> keyVector;

    for (auto iter : map)
    {
        keyVector.push_back(iter.second->GetKey());
    }

    if (ImGui::BeginCombo("##Texture", keyVector[item_current_idx].c_str(), flags))
    {
        for (int n = 0; n < keyVector.size(); ++n)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(keyVector[n].c_str(), is_selected))
            {
                item_current_idx = n;
                texture = &ResourcesManager<sf::Texture>::GetInstance().Get(keyVector[n]);
                sprite.setTexture(*texture);
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    // 텍스쳐	
    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
    sf::Vector2u resolution = {};

    ImTextureID tex_id = 0;
    if (nullptr != texture)
    {
        tex_id = (ImTextureID)texture->getNativeHandle();		//텍스쳐 존재 확인
        resolution = texture->getSize();
    }

    if (texture)
        ImGui::Image(tex_id, ImVec2(resolution), uv_min, uv_max, tint_col, border_col);

    ImGui::Text("FramSize"); ImGui::SameLine();
    if (ImGui::InputInt("##FramSize", &iAnimIndexSize))
    {
        if (animInfoVector.size() < iAnimIndexSize)
        {
            for (size_t i = animInfoVector.size(); i < iAnimIndexSize; ++i)
            {
                AnimationInfo info = {};
                if (i > 0)
                    info = animInfoVector[i - 1];

                animInfoVector.push_back(info);
            }
        }
        else if (animInfoVector.size() > iAnimIndexSize)
        {
            for (size_t i = animInfoVector.size(); i > iAnimIndexSize; --i)
            {
                //auto iter = m_vecAnimInfo.end();
                animInfoVector.pop_back();
            }
        }
    }

    static int frameID = 0;
    sf::Vector2f leftTop = {};
    sf::Vector2f frameSize = {};

    if (0 < animInfoVector.size())
    {
        ImGui::Text("FrameIndex"); ImGui::SameLine();
        if (ImGui::InputInt("##FrameIndex", &frameID))
            frameID = Utils::Clamp(frameID, 0, (int)animInfoVector.size() - 1);

        ImGui::Text("RectSize"); ImGui::SameLine();

        int rectSizeArr[2] = { (int)animInfoVector[frameID].rectSize.x, (int)animInfoVector[frameID].rectSize.y };
        if (ImGui::InputInt2("##RectSize", rectSizeArr))
        {
            animInfoVector[frameID].rectSize = { (unsigned int)rectSizeArr[0],(unsigned int)rectSizeArr[1] };
        }


        ImGui::Text("LeftPosition"); ImGui::SameLine(); 
        ImGui::InputInt("##LeftPosition", &animInfoVector[frameID].uvRect.left);
        ImGui::Text("WidthRange"); ImGui::SameLine();
        ImGui::InputInt("##WidthRange", &animInfoVector[frameID].uvRect.width);
        ImGui::Text("TopPosition"); ImGui::SameLine();
        ImGui::InputInt("##TopPosition", &animInfoVector[frameID].uvRect.top);
        ImGui::Text("HeightRange"); ImGui::SameLine();
        ImGui::InputInt("##HeightRange", &animInfoVector[frameID].uvRect.height);

        ImGui::Text("Duration"); ImGui::SameLine();
        ImGui::InputFloat("##Duration", &animInfoVector[frameID].duration);
        //ImGui::Text("Offset  "); ImGui::SameLine(); ImGui::InputFloat2("##Offset", (float*)&animInfoVector[frameID].vOffset);
         /*
         ImVec2 uv_0 = ImVec2(animInfoVector[frameID].vLeftTop.x / resolution.x, animInfoVector[frameID].vLeftTop.y / resolution.y);
         ImVec2 uv_1 = ImVec2(uv_0.x + animInfoVector[frameID].vFrmSize.x / resolution.x, uv_0.y + animInfoVector[frameID].vFrmSize.y / resolution.y);
         */
         ImVec2 size = ImVec2(64.0f, 64.0f);

        static char cName[100];
        ImGui::InputText("##edit", cName, 100);
        ImGui::SameLine();
        if (ImGui::Button("AnimName"))
        {
            // strName = cName;
            // wstrName = wstring(strName.begin(), strName.end());
        }

        sprite.setTextureRect(animInfoVector[frameID].uvRect);

        if (nullptr != texture) 
            ImGui::ImageButton(keyVector[item_current_idx].c_str(), sprite, { (float)animInfoVector[frameID].rectSize.x, (float)animInfoVector[frameID].rectSize.y });

        if (ImGui::Button("Play"))
        {
            frameID = 0;
            isPlay = true;
        }
        ImGui::SameLine(); 
        if (ImGui::Button("repeat"))
            isRepeat = !isRepeat;

        if (ImGui::Button("Anim Save"))
        {
            /*strName = cName;
            wstrName = wstring(strName.begin(), strName.end());

            for (size_t i = 0; i < m_vecAnimInfo.size(); i++)
            {
                m_vecAnimInfo[i].vFrmSize.x /= m_pTex->Width();
                m_vecAnimInfo[i].vFrmSize.y /= m_pTex->Height();
                m_vecAnimInfo[i].vLeftTop.x /= m_pTex->Width();
                m_vecAnimInfo[i].vLeftTop.y /= m_pTex->Height();
            }*/
            AnimationSave("");
        }

        if (isPlay) 
            AnimationPlay(frameID);
    }

    if (ImGui::Button("TexLoad")) TextureLoad();
    ImGui::SameLine(); if (ImGui::Button("AnimLoad")) AnimationLoad();


    ImGui::End();
}

void AnimationToolGUI::TextureLoad()
{
}

void AnimationToolGUI::AnimationSave(std::string animationName)
{
    // csv 세이브 되게 제작

}

void AnimationToolGUI::AnimationLoad()
{
    // csv 로드 하게 수정

}

void AnimationToolGUI::Listinit()
{
}

void AnimationToolGUI::AnimationPlay(int& iFrmID)
{
    accTime += TimeManager::GetInstance().GetDeletaTime();
    if (accTime >= animInfoVector[iFrmID].duration)
    {
        accTime -= animInfoVector[iFrmID++].duration;

        if (iFrmID == animInfoVector.size())
        {
            if (isRepeat)
                iFrmID = 0;
            else
            {
                --iFrmID;
                isPlay = false;
            }
        }
    }

}

void AnimationToolGUI::ChangeToolVersion()
{
}