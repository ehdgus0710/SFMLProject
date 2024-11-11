#include "ComponentGUI.h"

class AnimationGUI : public ComponentGUI
{
protected:
	Animator* animator;

public:
	virtual void update();
	void SetObject(GameObject* object);

public:
	AnimationGUI();
	~AnimationGUI();
};