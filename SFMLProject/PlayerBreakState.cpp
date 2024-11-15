#include "stdafx.h"
#include "PlayerBreakState.h"
#include "Rigidbody.h"
#include "Animator.h"

PlayerBreakState::PlayerBreakState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Run)
	, rigidbody(nullptr)
	, horizontal(0.f)
	, isMoveDirectionLeft(false)
{
}

PlayerBreakState::~PlayerBreakState()
{
}

void PlayerBreakState::Awake()
{
}

void PlayerBreakState::Start()
{
	rigidbody = player->GetRigidbody();
}
void PlayerBreakState::Enter()
{
	PlayerBaseState::Enter();
	player->GetAnimator()->ChangeAnimation("marioBreak", true);

	horizontal = InputManager::GetInstance().GetAxis(Axis::Horizontal);
	isMoveDirectionLeft = horizontal > 0.f ? false : true;
}

void PlayerBreakState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerBreakState::Update(float deltaTime)
{
	horizontal = InputManager::GetInstance().GetAxis(Axis::Horizontal);

	if (horizontal < 0.f && isMoveDirectionLeft)
		fsm->ChangeState(PlayerStateType::Run);
	else if (horizontal > 0.f && !isMoveDirectionLeft)
		fsm->ChangeState(PlayerStateType::Run);

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Space) || (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Space) && InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f))
	{
		fsm->ChangeState(PlayerStateType::Jump);
	}
}

void PlayerBreakState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ InputManager::GetInstance().GetAxis(Axis::Horizontal) * player->GetSpeed() , rigidbody->GetCurrentVelocity().y });
}