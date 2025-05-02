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
	collider.UpdateCollider(position, width, height);
	
	// fsm state update
	curState->ChangeStateLogic();
	curState->UpdateLogic();
}

void Player::Render()
{
	collider.DrawCollider();

	// fsm state render
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

/// ReSize - 현재 애니메이션의 프레임 크기로 플레이어 크기 조정
void Player::ReSize()
{
	width = currentAnimation->GetCurrentFrame().width;
	height = currentAnimation->GetCurrentFrame().height;
}

/*-------------------- Player Event --------------------*/
// Charge up hp
void Player::ChargeUp() 
{
	this->charge += 5;
	if (this->charge >= chargeMax)
	{
		this->charge = chargeMax;
		isChargeMax = true;
	}
	else
	{
		isChargeMax = false;
	}
}

// Charge downhp
void Player::ChargeDown()
{
	this->charge -= 5;
	if (this->charge <= 0)
	{
		this->charge = 0;
		isChargeMax = false;
	}
	else
	{
		isChargeMax = true;
	}
}

// MP up
void Player::MpUp() 
{
	this->mp += 5;
	if (this->mp >= maxMp)
	{
		this->mp = maxMp;
		isMpEmpty = false;
	}
	else
	{
		isMpEmpty = true;
	}
}

// MP down
void Player::MpDown()
{
	this->mp -= 5;
	if (this->mp <= 0)
	{
		this->mp = 0;
		isMpEmpty = true;
	}
	else
	{
		isMpEmpty = false;
	}
}

// Collision check
bool Player::isCollision(BoxCollider other)
{
	return this->collider.isCollision(other);
}

// Hit event
void Player::Hit(int damage) 
{
	this->hp -= damage;
	this->isHit = true;

	if (this->hp <= 0)
	{
		hp = 0;
		isDie = true;
		this->Die();
	}
}

// Die event
void Player::Die() 
{

}