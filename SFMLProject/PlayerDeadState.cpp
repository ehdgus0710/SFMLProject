#include "stdafx.h"
#include "PlayerDeadState.h"


PlayerDeadState::PlayerDeadState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dead)
{
}

PlayerDeadState::~PlayerDeadState()
{
}

void PlayerDeadState::Awake()
{
}

void PlayerDeadState::Start()
{
}

void PlayerDeadState::Enter()
{
}

void PlayerDeadState::Exit()
{
}

void PlayerDeadState::Update(float deltaTime)
{
}

void PlayerDeadState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerDeadState::LateUpdate(float deltaTime)
{
}