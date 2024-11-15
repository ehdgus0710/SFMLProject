#include "stdafx.h"
#include "PlayerBaseState.h"

PlayerBaseState::PlayerBaseState(PlayerStateType stateType)
	: BaseState<PlayerStateType>(stateType)
{
}

PlayerBaseState::~PlayerBaseState()
{
}

void PlayerBaseState::Awake()
{
}

void PlayerBaseState::Start()
{
}

void PlayerBaseState::Enter()
{
}

void PlayerBaseState::Exit()
{
}

void PlayerBaseState::Update(float deltaTime)
{
}

void PlayerBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerBaseState::LateUpdate(float deltaTime)
{
}
