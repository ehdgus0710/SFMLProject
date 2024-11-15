#include "stdafx.h"
#include "PlayerHitState.h"

PlayerHitState::PlayerHitState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Hit)
{
}

PlayerHitState::~PlayerHitState()
{
}

void PlayerHitState::Awake()
{
}

void PlayerHitState::Start()
{
}

void PlayerHitState::Enter()
{
}

void PlayerHitState::Exit()
{
}

void PlayerHitState::Update(float deltaTime)
{
}

void PlayerHitState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerHitState::LateUpdate(float deltaTime)
{
}
