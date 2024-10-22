#pragma once

#include "SpriteGameObject.h"

class Test : public SpriteGameObject
{
public:

	void Update(const float& deltaTime) override;

public:
	Test(const std::string& texId, const std::string& name = "");
	~Test();
};

