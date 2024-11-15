#pragma once

#include "BaseState.h"

class PlayerBaseState : public BaseState<PlayerStateType>
{
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	PlayerBaseState(PlayerStateType stateType);
	virtual ~PlayerBaseState();
};

