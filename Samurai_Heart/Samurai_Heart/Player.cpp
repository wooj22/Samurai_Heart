#include "Player.h"
#include "Idle.h"
#include "Run.h"
#include "Jump.h"


void Player::Start() 
{
	PlayerSpriteInit();
	PlayerAnimationInit();
	StateInit();
}

void Player::Update() 
{
	KeyInputHandler();
	ReSize();
	
	// fsm state logic
	curState->ChangeStateLogic();
	curState->UpdateLogic();
}

void Player::Render()
{
	curState->Render();
}


/*-------------------- Sprite & Animation --------------------*/
// sprite load
void Player::PlayerSpriteInit()
{
	idleSprite.Load(L"../Resource/Player/Idle.png");
	runSprite.Load(L"../Resource/Player/Run.png");
	jumpUpSprite.Load(L"../Resource/Player/JumpUp.png");
	jumpDownSprite.Load(L"../Resource/Player/JumpDown.png");
}

// animation load
void Player::PlayerAnimationInit()
{
	// idle
	idleAnimation.LoadFromFile("../Resource/Player/Idle.txt");
	idleAnimation.SetFrameDuration(0.1f);
	
	// run
	runAnimation.LoadFromFile("../Resource/Player/Run.txt");
	runAnimation.SetFrameDuration(0.1f);

	// jump down (jump up 1 frame)
	jumpDownAnimation.LoadFromFile("../Resource/Player/JumpDown.txt");
	jumpDownAnimation.SetFrameDuration(0.1f);
}

/*-------------------- FSM --------------------*/
/// State Init
void Player::StateInit() 
{
	// fsm state class 등록
	stateArr[IDLE] = new Idle(this);
	stateArr[RUN] = new Run(this);
	stateArr[JUMP] = new Jump(this);

	// state set
	curPlayerState = IDLE;
	curState = stateArr[curPlayerState];
	ChangeState(curPlayerState);
}

/// State Change
void Player::ChangeState(PlayerState newState) 
{
	if (curState) curState->Exit();
	
	curPlayerState = newState;
	curState = stateArr[curPlayerState];
	curState->Enter();
}

/*-------------------- Update --------------------*/
/// Key Input Handler
void Player::KeyInputHandler() 
{
	// move key
	if (InputManager::Get().GetKeyDown(MoveLKey))
		isMoveLKey = true;
	if (InputManager::Get().GetKeyUP(MoveLKey))
		isMoveLKey = false;
	if (InputManager::Get().GetKeyDown(MoveRKey))
		isMoveRKey = true;
	if (InputManager::Get().GetKeyUP(MoveRKey))
		isMoveRKey = false;

	// jump key
	if (InputManager::Get().GetKeyDown(JumpKey))
		isJumpKey = true;
	if (InputManager::Get().GetKeyUP(JumpKey))
		isJumpKey = false;

	// attack key
	if (InputManager::Get().GetKeyDown(AttackKey))
		isAttackKey = true;
	if (InputManager::Get().GetKeyUP(AttackKey))
		isAttackKey = false;
	if (InputManager::Get().GetKeyDown(SpecialAttackKey))
		isSpecialAttackKey = true;
	if (InputManager::Get().GetKeyUP(SpecialAttackKey))
		isSpecialAttackKey = false;

	// defense key
	if (InputManager::Get().GetKeyDown(DefenseKey))
		isDefenseKey = true;
	if (InputManager::Get().GetKeyUP(DefenseKey))
		isDefenseKey = false;
}

/// ReSize
void Player::ReSize()
{
	// 현재 animation 사이즈 get -> 멤버에 반영
	
	// collider update
	collider.UpdateCollider(position, width, height);
}

/*-------------------- Player Event --------------------*/
void Player::ChargeUp() 
{

}

void Player::ChargeDown()
{

}

void Player::MpUp() 
{


}
void Player::MpDown()
{

}

bool Player::isCollision(BoxCollider other)
{
	return this->collider.isCollision(other);
}

void Player::Hit(int damage) 
{

}

void Player::Die() 
{

}