#include "stdafx.h"
#include "PlayerFSM.h"

#include "PlayerIdleState.h"
#include "PlayerBreakState.h"
#include "PlayerRunState.h"
#include "PlayerJumpState.h"
#include "PlayerDeadState.h"
#include "PlayerBaseState.h"

PlayerFSM::PlayerFSM(Player* owner)
	: owner(owner)
{
}

PlayerFSM::~PlayerFSM()
{
}

void PlayerFSM::Awake()
{
	CreateAllState();
}

void PlayerFSM::Start()
{
}

void PlayerFSM::CreateAllState()
{
	for (int i = 0; i < (int)PlayerStateType::End; ++i)
	{
		switch ((PlayerStateType)i)
		{
		case PlayerStateType::Idle:
			AddState(PlayerStateType::Idle);
			break;
		case PlayerStateType::Run:
			AddState(PlayerStateType::Run);
			break;
		case PlayerStateType::Break:
			AddState(PlayerStateType::Break);
			break;
		case PlayerStateType::Jump:
			AddState(PlayerStateType::Jump);
			break;
		case PlayerStateType::Hit:
			AddState(PlayerStateType::Hit);
			break;
		case PlayerStateType::Dead:
			AddState(PlayerStateType::Dead);
			break;
		case PlayerStateType::End:
			break;
		default:
			break;
		}
	}
}

BaseState<PlayerStateType>* PlayerFSM::CreateState(PlayerStateType type)
{
	PlayerBaseState* state = nullptr;

	switch (type)
	{
	case PlayerStateType::Idle:
		return new PlayerIdleState();
	case PlayerStateType::Run:
		return new PlayerIdleState();
	case PlayerStateType::Break:
		return new PlayerIdleState();
	case PlayerStateType::Jump:
		return new PlayerIdleState();
	case PlayerStateType::Hit:
		return new PlayerIdleState();
	case PlayerStateType::Dead:
		return new PlayerIdleState();
	case PlayerStateType::End:
		break;
	default:
		break;
	}

	return nullptr;
}

void PlayerFSM::Update(float deltaTime)
{
	stateMap[currentStateType]->Update(deltaTime);
}

void PlayerFSM::FixedUpdate(float fixedDeltaTime)
{
	stateMap[currentStateType]->FixedUpdate(fixedDeltaTime);
}

void PlayerFSM::LateUpdate(float deltaTime)
{
	stateMap[currentStateType]->LateUpdate(deltaTime);
}
