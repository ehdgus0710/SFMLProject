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

    //if (ImGui::BeginCombo("##Texture", m_vecTexList[item_current_idx].c_str(), flags))
    //{
    //    for (int n = 0; n < m_vecTexList.size(); n++)
    //    {
    //        const bool is_selected = (item_current_idx == n);
    //        if (ImGui::Selectable(m_vecTexList[n].c_str(), is_selected))
    //        {
    //            item_current_idx = n;
    //            m_strTexName = wstring(m_vecTexList[n].begin(), m_vecTexList[n].end());
    //            m_pTex = CResMgr::GetInst()->FindRes<CTexture>(m_strTexName).Get();
    //        }

    //        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
    //        if (is_selected)
    //            ImGui::SetItemDefaultFocus();
    //    }
    //    ImGui::EndCombo();
    //}

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
        //if (m_vecAnimInfo.size() < iAnimIndexSize)
        //{
        //    for (size_t i = m_vecAnimInfo.size(); i < iAnimIndexSize; ++i)
        //    {
        //        tAnimFrm info = {};
        //        m_vecAnimInfo.push_back(info);
        //    }
        //}
        //else if (m_vecAnimInfo.size() > iAnimIndexSize)
        //{
        //    for (size_t i = m_vecAnimInfo.size(); i > iAnimIndexSize; --i)
        //    {
        //        //auto iter = m_vecAnimInfo.end();
        //        m_vecAnimInfo.pop_back();
        //    }
        //}
    }

    static int iFrmID = 0;
    sf::Vector2f leftTop = {};
    sf::Vector2f frameSize = {};

    if (0 < animInfoVector.size())
    {
       /* ImGui::Text("FrmID   "); ImGui::SameLine(); ImGui::InputInt("##FrmID", &iFrmID);
        if (0 > iFrmID) iFrmID = 0; else if (animInfoVector.size() <= iFrmID) iFrmID = (int)animInfoVector.size() - 1;

        ImGui::Text("FrmSize "); ImGui::SameLine();

        ImGui::InputFloat2("##FrmSize", (float*)&animInfoVector[iFrmID].vFrmSize);

        ImGui::Text("LeftTop "); ImGui::SameLine(); ImGui::InputFloat2("##LeftTop", (float*)&animInfoVector[iFrmID].vLeftTop);

        ImGui::Text("Offset  "); ImGui::SameLine(); ImGui::InputFloat2("##Offset", (float*)&animInfoVector[iFrmID].vOffset);
        ImGui::Text("Duration"); ImGui::SameLine();
        ImGui::InputFloat("##Duration", &animInfoVector[iFrmID].fDuration);*/

        // ImVec2 uv_0 = ImVec2(animInfoVector[iFrmID].vLeftTop.x / resolution.x, animInfoVector[iFrmID].vLeftTop.y / resolution.y);
        // ImVec2 uv_1 = ImVec2(uv_0.x + animInfoVector[iFrmID].vFrmSize.x / resolution.x, uv_0.y + animInfoVector[iFrmID].vFrmSize.y / resolution.y);
        // ImVec2 size = ImVec2(64.0f, 64.0f);

        static char cName[100];
        ImGui::InputText("##edit", cName, 100);
        ImGui::SameLine();
        if (ImGui::Button("AnimName"))
        {
            // strName = cName;
            // wstrName = wstring(strName.begin(), strName.end());
        }

      /*  if (nullptr != texture) 
            ImGui::ImageButton((ImTextureID)texture->getNativeHandle(), size, uv_0, uv_1);*/

        if (ImGui::Button("Play"))
        {
            iFrmID = 0;
            isPlay = true;
        }
        ImGui::SameLine(); 
        if (ImGui::Button("repeat"))
            isRepeat != isRepeat;

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

        if (isPlay) AnimationPlay(iFrmID);
    }

    if (ImGui::Button("TexLoad")) TextureLoad();
    ImGui::SameLine(); if (ImGui::Button("AnimLoad")) AnimationLoad(iAnimIndexSize);


    ImGui::End();
}

void AnimationToolGUI::TextureLoad()
{
}

void AnimationToolGUI::AnimationSave(std::string animationName)
{
}

void AnimationToolGUI::AnimationLoad(int& iSize)
{
}

void AnimationToolGUI::Listinit()
{
}

void AnimationToolGUI::AnimationPlay(int& iFrmID)
{
}

void AnimationToolGUI::ChangeToolVersion()
{
}