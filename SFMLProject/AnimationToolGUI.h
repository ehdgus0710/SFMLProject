#pragma once

#include "GUI.h"
#include "Animation.h"

class AnimationToolGUI : public GUI
{

private:
    sf::Sprite                  sprite;
    sf::Texture*                texture;
    std::vector<std::string>    textureVector;
    std::vector<AnimationInfo>  animInfoVector;
    std::string                 textureID;

    sf::Vector2u                rectSize;
    sf::Vector2u                atlasRectSize;

    static int                  frameID;
    float                       accTime;
    bool                        isPlay;
    bool                        isRepeat;
    bool                        isButton;
    bool                        isAtlasTextrue;

public:
    void Init() override;
    void Update() override;

    void TextureLoad();
    void AnimationSave(const std::string& animationName);
    void AnimationLoad();
private:
    void Listinit();
    void AnimationPlay(int& iFrmID);
    void ChangeToolVersion();
    void AtlasTextrue();
    void DefaultTextrue();

public:
    AnimationToolGUI();
    ~AnimationToolGUI();
};
